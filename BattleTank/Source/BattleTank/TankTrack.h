// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * Tank track is used to set maximum driving force , and apply forces to the tank
 */
UCLASS(ClassGroup=(Custom),meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
private:
	UTankTrack();
	UFUNCTION(BlueprintCallable)
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	float CurrentThrottle = 0.0f;
	void DriveTrack();
protected:
	virtual void BeginPlay() override;
	
	void ApplySidewayForce( );
	
public:
	//Set throttle between -1 and +1

	UFUNCTION(BlueprintCallable,Category = Input)
	void SetThrottle(float Throttle);
	
	//Max force per track 
	UPROPERTY(EditDefaultsOnly)
		float TrackMaxDrivingForce = 400000/2; //Assume  40 tonne tank, and 1g accelleration 
	
	
};
