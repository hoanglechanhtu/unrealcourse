// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
 
#include "TankAimingComponent.h"
#include "TankAIController.h"


void ATankAIController::BeginPlay() {
	Super::BeginPlay();
	TankAimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	UE_LOG(LogTemp, Warning, TEXT("Ai tank move to actor"));
}

void ATankAIController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!ensure(PlayerTank)) {
		return;
	}
	//  move toward the player
	MoveToActor(PlayerTank, AcceptanceRadius); //TODO check radius is in cm
	
	//Aimt toweard the player
	if (!ensure(TankAimingComponent)) { return; }
	 
	TankAimingComponent->AimAt(PlayerTank->GetActorLocation(),LaunchSpeed);

	//TODO fire if ready
	TankAimingComponent->Fire(LaunchSpeed);
	
}
 

 