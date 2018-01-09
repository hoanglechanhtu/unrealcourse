// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

/**
 * 
 */
UCLASS(ClassGroup=(Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()
	


public:
	void Rotator(float RelativeSpeed);
private:
	UPROPERTY(EditAnywhere, Category = Setup)
		float MaxDegreePerSecond = 5;
	UPROPERTY(EditAnywhere, Category = Setup)
		float MaxRotationDegree = 180;
	UPROPERTY(EditAnywhere, Category = Setup)
		float MinRotationDegree = -180;
	
	
};
