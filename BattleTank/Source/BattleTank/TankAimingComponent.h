// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EFiringStatus : uint8 {
	Reloading,
	Aiming,
	Locked


};

class UTankBarrel;
class UTankTurret;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	void SetBarrelRef(UTankBarrel* BarrelToSet);

	void SetTurretRef(UTankTurret* TurretToSet);
	
	UTankBarrel* Barrel = nullptr;
	
	UTankTurret* Turret = nullptr;
protected:
	 
	UPROPERTY(BlueprintReadOnly,Category ="State")
		EFiringStatus State = EFiringStatus::Reloading;

	void MoveBarrelToward(FVector AimDirection);
	void RotatorTurret(FVector AimDirection);
public:	
	 

	void AimAt(FVector HitLocation,float LaunchSpeed);
		
	
};
