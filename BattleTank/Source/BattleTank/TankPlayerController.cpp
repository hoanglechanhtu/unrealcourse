// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankPlayerController.h"




ATank* ATankPlayerController::GetControlledTank() const {
	// getPawn -> parent class (PlayerController)
	return Cast<ATank>(GetPawn());
};