// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAIController.h"


void ATankAIController::BeginPlay() {
	Super::BeginPlay();
	auto ControlledTank = GetControlledTank();
	if (!ControlledTank) {	
		UE_LOG(LogTemp, Warning, TEXT("TankAIController no possesing tank"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Controlled Tank : %s"), *(ControlledTank->GetName()));
	}
	
	auto PlayerTank = GetPlayerControlledTank();
	if (!PlayerTank) {
		UE_LOG(LogTemp, Warning, TEXT("Cant find player tank"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Player Controlled Tank : %s"), *(PlayerTank->GetName()));
	}
}

void ATankAIController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	if (GetPlayerControlledTank()) {
		//TODO move toward the player

		//Aimt toweard the player
		GetControlledTank()->AimAt(GetPlayerControlledTank()->GetActorLocation());

		//TODO fire if ready
	}
}
ATank* ATankAIController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
}



ATank* ATankAIController::GetPlayerControlledTank() const {
	auto PlayerController = GetWorld()->GetFirstPlayerController();

	if (!PlayerController) {
		UE_LOG(LogTemp, Warning, TEXT("Cant find PlayerController"));
		return nullptr;
	}
	else {

		auto tank = Cast<ATank>(PlayerController->GetPawn());
		return tank;

	}

};