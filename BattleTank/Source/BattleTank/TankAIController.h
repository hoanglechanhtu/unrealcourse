// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * Help AI tank to find path to player tank
 */
class ATank;
class UTankAimingComponent;

UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
private:

	UTankAimingComponent* TankAimingComponent = nullptr;

	ATank* GetControlledTank() const;
	ATank* GetPlayerControlledTank() const;
	//How close  ai tank get close to player
	float AcceptanceRadius = 3000;
};
