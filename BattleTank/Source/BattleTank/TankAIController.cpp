// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"
#include "TankAimingComponent.h"
#include "TankAIController.h"


void ATankAIController::SetPawn(APawn* InPawn) {
	Super::SetPawn(InPawn);
	if (InPawn) {
		auto PossesedTank = Cast<ATank>(InPawn);
		if (!ensure(PossesedTank)) { return; }
		else {
			//register to listen tank delegate on deadth
			PossesedTank->OnDeadth.AddUniqueDynamic(this, &ATankAIController::OnTankDeadth);


		}
	}


}

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

	//if aim or lock then fire
	if (TankAimingComponent->GetFiringState() == EFiringStatus::Locked) {
		TankAimingComponent->Fire(LaunchSpeed);
	}

	
}
 

void ATankAIController::OnTankDeadth() {
	auto TankName = Cast<ATank>(GetPawn())->GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s:Someone die"), *TankName);
}
 