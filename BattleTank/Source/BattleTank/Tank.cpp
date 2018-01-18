// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
 
#include "Tank.h"
 
// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	 
	 
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	 
	 
}

 

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

 
float ATank::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController* EventInstigator, AActor* DamageCauser) {
	const float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	int32 ClampDamage = FMath::Clamp<int32>(ActualDamage, 0, TankCurrentHP);
	TankCurrentHP -= ClampDamage;
	if(TankCurrentHP<=0)
		UE_LOG(LogTemp, Warning, TEXT("Tank : %s die"),*GetName());
	return ClampDamage;
}