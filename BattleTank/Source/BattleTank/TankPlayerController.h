// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"
#define OUT	//
/**
 * 
 */

class ATank;
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
private:
	

	void AimTowardCrosshair();
	//Return an out parameter, true if hits landscape
	bool GetSightRayHitLocation(FVector& OutHitLocation ) const;

	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;

	bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;
public:
	ATank* GetControlledTank() const;


	virtual void  BeginPlay() override;
	
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere)
		float CrosshairXLocation = 0.5;
	UPROPERTY(EditAnywhere)
		float CrosshairYLocation = 0.3333;

	UPROPERTY(EditAnywhere)
		float LineTraceRange= 1000000;
};
