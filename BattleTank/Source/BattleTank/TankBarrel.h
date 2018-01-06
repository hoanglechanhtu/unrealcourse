// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))

class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
	
public:
	void Elevate(float RelativeSpeed);
private:
	UPROPERTY(EditAnywhere, Category = Setup)
		float MaxDegreePerSecond = 20;
	UPROPERTY(EditAnywhere, Category = Setup)
		float MaxElavationDegree  =45 ;
	UPROPERTY(EditAnywhere, Category = Setup)
		float MinElavationDegree = 0;
};
