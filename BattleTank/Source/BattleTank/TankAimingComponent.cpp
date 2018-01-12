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

	if (bIsReady&&Barrel) {

		//TODO spawn a projectile
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(BlueprintProjectile, Barrel->GetSocketLocation(FName("Projectile")), Barrel->GetSocketRotation(FName("Projectile")));

		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}
}

void UTankAimingComponent::MoveBarrelToward(FVector AimDirection) {
	// Workout difference bettween current barrel reaction and aimdirection
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
 
	if (!ensure(Turret)) {
	 
		return;
	
	}
	
	FRotator CurrrentTurretRotator = Turret->GetForwardVector().Rotation();
	FRotator AimRotator = AimDirection.Rotation();

	auto DeltaRotator = AimRotator - CurrrentTurretRotator;

	Turret->Rotator(DeltaRotator.Yaw);

}