// Fill out your copyright notice in the Description page of Project Settings.

#include "MovingPlatform.h"

AMovingPlatform::AMovingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;

	// To make actor moveable.
	SetMobility(EComponentMobility::Movable);
}

void AMovingPlatform::BeginPlay()
{
	// Override.
	Super::BeginPlay();

	if (HasAuthority())
	{
		SetReplicates(true);
		SetReplicateMovement(true);
	}	
}

void AMovingPlatform::Tick(float DeltaTime) 
{
	// Override.
	Super::Tick(DeltaTime);

	// Check whether this is server or not.
	if (HasAuthority())
	{
		// Get actor location.
		FVector Location = GetActorLocation();
		// Move the actor.
		Location += FVector(Speed * DeltaTime, 0, 0);
		SetActorLocation(Location);
	}
}
