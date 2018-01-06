// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"


#include "TankPlayerController.h"



void ATankPlayerController::BeginPlay() {
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("TankPlayerContrller-Begin play"));
	auto ControlledTank = GetControlledTank();

	if (ControlledTank  ) {
		UE_LOG(LogTemp, Warning, TEXT("Tank id : %s"), *(ControlledTank->GetName()));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("PlayerController not posseing a tank"));
	}
}

void ATankPlayerController :: Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	AimTowardCrosshair();
	UE_LOG(LogTemp, Warning, TEXT("Tick tick tick"));
}

ATank* ATankPlayerController::GetControlledTank() const {
	// getPawn -> parent class (PlayerController)
	return Cast<ATank>(GetPawn());
};

void ATankPlayerController::AimTowardCrosshair() {
	if (!GetControlledTank()) { return; }

	FVector HitLocation; // Out parameter 

	//Get world location if linetrace through crosshair
	// If it hits the landscape
	// Tell controlled tank to aim at this

	if (GetSightRayHitLocation(HitLocation)) { // has side-effect, is going to line trace
	
		GetControlledTank()->AimAt(HitLocation);
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
		
		GetLookVectorHitLocation(LookDirection, OutHitLocation);
		 
	}


	
	

	return true;
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