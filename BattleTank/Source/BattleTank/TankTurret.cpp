// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTurret.h"


void UTankTurret::Rotator(float RelativeSpeed) {

	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	auto RotationChange = RelativeSpeed*MaxDegreePerSecond*GetWorld()->DeltaTimeSeconds;
	auto RawNewRotation = RelativeRotation.Yaw + RotationChange;
	auto Rotation = FMath::Clamp<float>(RawNewRotation, MinRotationDegree, MaxRotationDegree);
	
	SetRelativeRotation(FRotator(0, Rotation, 0));
}

