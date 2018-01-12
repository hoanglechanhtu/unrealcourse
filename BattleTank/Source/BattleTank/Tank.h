// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

 
#include "GameFramework/Pawn.h"

#include "Tank.generated.h"

 
 
 
 
UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
 
 
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable,Category="Firing")
		float GetLaunchSpeed() { return LaunchSpeed; }
 

private:

	UPROPERTY(EditAnywhere, Category = Firing)
		float LaunchSpeed = 8000; //TODO find sensible value

 

	
};
