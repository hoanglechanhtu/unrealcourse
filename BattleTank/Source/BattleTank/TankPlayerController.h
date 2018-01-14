// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"
#define OUT	//
/**
 * Responsible to helping the  player aim
 */

class ATank;
class UTankAimingComponent;


UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
		
protected:
	 
	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
		void FoundAimingComponent(UTankAimingComponent* AimingCompRef);
private:
	UPROPERTY(EditAnywhere, Category = Firing)
		float LaunchSpeed = 8000; //TODO find sensible value

	UTankAimingComponent* TankAimingComponent=nullptr;
	void AimTowardCrosshair();
	//Return an out parameter, true if hits landscape
	bool GetSightRayHitLocation(FVector& OutHitLocation ) const;

	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;

	bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;
public:


	virtual void  BeginPlay() override;
	
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere)
		float CrosshairXLocation = 0.5;
	UPROPERTY(EditAnywhere)
		float CrosshairYLocation = 0.33;

	UPROPERTY(EditAnywhere)
		float LineTraceRange= 1000000;
};
