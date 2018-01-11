// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet) {
	if (!LeftTrackToSet || !RightTrackToSet) { return; }
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;

}
void UTankMovementComponent::IntendMoveForward(float Throw) {

	 
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
	

}

void UTankMovementComponent::TurnRight(float Throw) {

	
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);

}



void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) {
	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();
	
	//Move forward
	auto ForwardThrow = FVector::DotProduct(TankForward, AIForwardIntention);
	IntendMoveForward(ForwardThrow);
	//Turn right
	auto TurnRightThrow = FVector::CrossProduct(TankForward, AIForwardIntention).Z;
	TurnRight(TurnRightThrow);

}