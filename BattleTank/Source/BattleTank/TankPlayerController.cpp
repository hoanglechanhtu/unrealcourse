// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "Tank.h"
#include "TankPlayerController.h"



void ATankPlayerController::BeginPlay() {
	Super::BeginPlay();
	
	TankAimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(TankAimingComponent)) {
		return;
	}
	else {
		FoundAimingComponent(TankAimingComponent);
	}
}

void ATankPlayerController :: Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	AimTowardCrosshair();
	 
}

 

void ATankPlayerController::AimTowardCrosshair() {
	 
	if (!ensure(TankAimingComponent)) {
		return;
	}
 
	FVector HitLocation; // Out parameter 

	
	//Get world location if linetrace through crosshair
	// If it hits the landscape
	// Tell controlled tank to aim at this
	bool bGotHitLocation = GetSightRayHitLocation(HitLocation);
	UE_LOG(LogTemp, Warning, TEXT("bGotHitLocation: %i"), bGotHitLocation);
	if (bGotHitLocation) { // has side-effect, is going to line trace
	
	 
		TankAimingComponent->AimAt(HitLocation, LaunchSpeed);

	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const {

	//Find the crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	
	auto ScreenLocation = FVector2D(CrosshairXLocation*ViewportSizeX, CrosshairYLocation*ViewportSizeY);
	
	FVector LookDirection;
	
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		// Line trace along look direction, and see what we hit
		
		return	GetLookVectorHitLocation(LookDirection, OutHitLocation);
		 
	}


	
	

	return false;
}


bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection)const {
	FVector CameraWorldLocation; // => ignore, it's camare world location
	
	return DeprojectScreenPositionToWorld(ScreenLocation.X, 
									   ScreenLocation.Y, 
		                               CameraWorldLocation, 
									   LookDirection);
	
}


bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const {
	FHitResult HitResult;
	auto Start = PlayerCameraManager->GetCameraLocation();
	auto End = Start + (LookDirection*LineTraceRange);
	
	if (GetWorld()->LineTraceSingleByChannel(
			HitResult,
			Start,
			End,
		ECollisionChannel::ECC_Visibility)
	) {
		// if linetrace succeed
		// set hitlocation
	
		HitLocation = HitResult.Location;
		return true;
	}
	else { 
		HitLocation = FVector(0.f);
		return false; 
	}
}