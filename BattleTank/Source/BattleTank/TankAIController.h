// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * Help AI tank to find path to player tank
 */
 
class UTankAimingComponent;

UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetPawn(APawn* InPawn) override;
private:
	UPROPERTY(EditAnywhere, Category = Firing)
		float LaunchSpeed = 8000; //TODO find sensible value

	UTankAimingComponent* TankAimingComponent = nullptr;

	 
	 
	//How close  ai tank get close to player
	UPROPERTY(EditAnywhere)
		float AcceptanceRadius = 3000;
	//On possesed tank deadth
	UFUNCTION()
		void OnTankDeadth();
};
