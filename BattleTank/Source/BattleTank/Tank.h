// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankAimingComponent;
class UTankTurret;
class UTankBarrel;
class AProjectile;
UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
 
	UFUNCTION(BlueprintCallable,Category=Setup)
		void Fire();
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void AimAt(FVector HitLocation);
	UFUNCTION(BlueprintCallable,Category = Setup)
		void SetBarrelRef(UTankBarrel* BarrelToSet);

	UFUNCTION(BlueprintCallable, Category = Setup)
		void SetTurretRef(UTankTurret* TurretToSet);

	UPROPERTY(EditAnywhere, Category = Setup)
		TSubclassOf<AProjectile> BlueprintProjectile;


protected:

	

	UTankAimingComponent* TankAimingComponent = nullptr;

private:

	UPROPERTY(EditAnywhere, Category = Firing)
		float LaunchSpeed = 100000; //TODO find sensible value
	//Local barrel to spawn projectile
	UTankBarrel* Barrel = nullptr;
	
	
};
