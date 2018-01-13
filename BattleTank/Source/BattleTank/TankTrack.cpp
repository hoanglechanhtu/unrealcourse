// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTrack.h"


/*
How can we deal with friction
	Set track max driving force
	Create physics matierial
	Apply for both track


*/

UTankTrack::UTankTrack() {
	PrimaryComponentTick.bCanEverTick = true; //TODO do we really need tick?
	
}

void UTankTrack::BeginPlay() {
	Super::BeginPlay();
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
	
}
 
void UTankTrack::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	//Calculate the slippage speed
	auto TankVelocity = GetComponentVelocity();
	auto TankRightVector = GetRightVector(); 
	auto SlippageSpeed = FVector::DotProduct(TankVelocity,TankRightVector);
	//Work-out the required acceleration this frame to correct
	auto CorrectionAcceleration = -(SlippageSpeed / DeltaTime)*GetRightVector();
	// Calculate and apply sideways for (F=ma)
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce = TankRoot->GetMass()*CorrectionAcceleration/2;
	TankRoot->AddForce(CorrectionForce);
	
}
void UTankTrack::SetThrottle(float Throttle) {
	auto TrackName = GetName();
	
	//TODO clamp actual throttle value so player cant over drive
	auto ForceApplied = GetForwardVector()*Throttle*TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {

	UE_LOG(LogTemp, Warning, TEXT("Tank track hit ground"));
}