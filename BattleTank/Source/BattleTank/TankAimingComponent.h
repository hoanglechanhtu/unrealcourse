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
class AProjectile;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	
	
	UFUNCTION(BlueprintCallable, Category = Setup)
		void Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);
	

	UFUNCTION(BlueprintCallable, Category = Setup)
		void Fire(float LaunchSpeed);
	
	UPROPERTY(EditAnywhere, Category = Setup)
		TSubclassOf<AProjectile> BlueprintProjectile;

	UTankBarrel* Barrel = nullptr;
	
	UTankTurret* Turret = nullptr;
protected:
	 
	UPROPERTY(BlueprintReadOnly, Category = "State")
		EFiringStatus State;

	void MoveBarrelToward(FVector AimDirection);
	void RotatorTurret(FVector AimDirection);

	UPROPERTY(EditDefaultsOnly)
		float ReloadFireTime = 3;

	float LastFireTime = 0;
	//Local barrel to spawn projectile
 

public:	
	 

	void AimAt(FVector HitLocation,float LaunchSpeed);
		
	
};
