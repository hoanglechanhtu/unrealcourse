// Fill out your copyright notice in the Description page of Project Settings.



#include "BattleTank.h"
#include "TankAimingComponent.h"
#include  "Projectile.h"
#include "TankBarrel.h"
#include "TankTurret.h"
// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true; //TODO do we really need tick?
	State= EFiringStatus::Aiming;
	// ...
}

void UTankAimingComponent::BeginPlay() {
	Super::BeginPlay();
	LastFireTime = FPlatformTime::Seconds();
}
 
void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) {
	
	if ((FPlatformTime::Seconds() - LastFireTime) < ReloadFireTime)
	{
		State = EFiringStatus::Reloading;
	}
	else if (RoundsLeft == 0) {
		State = EFiringStatus::OutOfAmmo;
	}
	else if(IsBarrelMoving()) {
		State = EFiringStatus::Aiming;
	
	}
	else {
		State = EFiringStatus::Locked;
	}

}
 
void UTankAimingComponent::AimAt(FVector HitLocation,float LaunchSpeed) {
	if (!ensure(Barrel)) { 
	 
		return; 
		
	}
	FVector TossVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		GetWorld(),
		TossVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0.0f,
		0.0f,
		ESuggestProjVelocityTraceOption::DoNotTrace
	); 
	
	if(bHaveAimSolution){

		//Calculate LaunchDirection

		FVector DesireAimDirection = TossVelocity.GetSafeNormal();
		MoveBarrelToward(DesireAimDirection);
		RotatorTurret(DesireAimDirection);
		
		 
	}
	 
	 
}

void UTankAimingComponent::Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet) {
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}



void UTankAimingComponent::Fire(float LaunchSpeed) {

	bool bIsReady = (FPlatformTime::Seconds() - LastFireTime) > ReloadFireTime;

	if (State != EFiringStatus::Reloading&& State != EFiringStatus::OutOfAmmo) {
		if (!ensure(Barrel)) { return; }
		if (!ensure(BlueprintProjectile)) { return; }
		//TODO spawn a projectile
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(BlueprintProjectile, Barrel->GetSocketLocation(FName("Projectile")), Barrel->GetSocketRotation(FName("Projectile")));

		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
		RoundsLeft--;
	}
}

void UTankAimingComponent::MoveBarrelToward(FVector AimDirection) {
	// Workout difference bettween current barrel reaction and aimdirection
	BarrelAimDirection = AimDirection;
	if (!ensure(Barrel)) { 

		 
		return;
	}
	FRotator CurrentBarrelRotator = Barrel->GetForwardVector().Rotation();
	FRotator AimRotator = AimDirection.Rotation();
	
	auto DeltaRotator = AimRotator - CurrentBarrelRotator;
	//Move the barrel the right amount this frame
	// Given a max elavation speed, and the frame time

	Barrel->Elevate(DeltaRotator.Pitch); 

	
}


void UTankAimingComponent::RotatorTurret(FVector AimDirection) {
	BarrelAimDirection = AimDirection;
	if (!ensure(Turret)) {
	 
		return;
	
	}
	
	FRotator CurrrentTurretRotator = Turret->GetForwardVector().Rotation();
	FRotator AimRotator = AimDirection.Rotation();

	auto DeltaRotator = AimRotator - CurrrentTurretRotator;
	if(FMath::Abs(DeltaRotator.Yaw)<180)
		Turret->Rotator(DeltaRotator.Yaw);
	else
		Turret->Rotator(-DeltaRotator.Yaw);
}

bool UTankAimingComponent::IsBarrelMoving() {
	if (!ensure(Barrel)) { return false; }
	return !(Barrel->GetForwardVector().Equals(BarrelAimDirection,0.01));

}




EFiringStatus UTankAimingComponent::GetFiringState() const{
	return State;
}




int UTankAimingComponent::GetRoundsLeft() const {
	return RoundsLeft;


}