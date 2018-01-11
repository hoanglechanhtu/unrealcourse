// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTrack.h"


/*
How can we deal with friction
	Set track max driving force
	Create physics matierial
	Apply for both track


*/

void UTankTrack::SetThrottle(float Throttle) {
	auto TrackName = GetName();
	
	//TODO clamp actual throttle value so player cant over drive
	auto ForceApplied = GetForwardVector()*Throttle*TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}