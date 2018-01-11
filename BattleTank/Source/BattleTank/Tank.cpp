// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "Tank.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "TankMovementComponent.h"
 

#include "Projectile.h"
// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming component"));
	 
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	 
	
}

 

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


void ATank::AimAt(FVector HitLocation) {
	TankAimingComponent->AimAt(HitLocation,LaunchSpeed);
	
}


void ATank::SetBarrelRef(UTankBarrel* BarrelToSet) {
	TankAimingComponent->SetBarrelRef(BarrelToSet);
	Barrel = BarrelToSet;
}

void ATank::SetTurretRef(UTankTurret* TurretToSet) {
	TankAimingComponent->SetTurretRef(TurretToSet);
}


void ATank::Fire() {
	
	bool bIsReady = (FPlatformTime::Seconds() - LastFireTime) > ReloadFireTime;
	if (bIsReady&&Barrel) {

		//TODO spawn a projectile
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(BlueprintProjectile, Barrel->GetSocketLocation(FName("Projectile")), Barrel->GetSocketRotation(FName("Projectile")));

		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}
}