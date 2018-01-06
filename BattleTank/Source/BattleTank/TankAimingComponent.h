// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

class UTankBarrel;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	void SetBarrelRef(UTankBarrel* BarrelToSet);

	void SetTurretRef(UStaticMeshComponent* TurretToSet);
	UTankBarrel* Barrel = nullptr;
	UStaticMeshComponent* Turret = nullptr;
protected:
	 

	void MoveBarrelToward(FVector AimDirection);
public:	
	 

	void AimAt(FVector HitLocation,float LaunchSpeed);
		
	
};
