// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"
#include "TankAimingComponent.h"
#include "TankAIController.h"


void ATankAIController::BeginPlay() {
	Super::BeginPlay();
	TankAimingComponent = GetControlledTank()->FindComponentByClass<UTankAimingComponent>();
}

void ATankAIController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	auto PlayerTank = GetPlayerControlledTank();
	if (!ensure(PlayerTank)) {
		return;
	}
	//  move toward the player
	MoveToActor(PlayerTank, AcceptanceRadius); //TODO check radius is in cm
	//Aimt toweard the player
	if (!ensure(TankAimingComponent)) { return; }
	 
	TankAimingComponent->AimAt(PlayerTank->GetActorLocation(),PlayerTank->GetLaunchSpeed());

	//TODO fire if ready
	GetControlledTank()->Fire();
	
}
ATank* ATankAIController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
}



ATank* ATankAIController::GetPlayerControlledTank() const {
	auto PlayerController = GetWorld()->GetFirstPlayerController();

	if (!ensure(PlayerController)) {
		 
		return nullptr;
	}
	else {

		auto tank = Cast<ATank>(PlayerController->GetPawn());
		return tank;

	}

};