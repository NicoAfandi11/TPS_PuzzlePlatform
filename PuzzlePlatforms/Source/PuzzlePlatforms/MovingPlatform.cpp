// Fill out your copyright notice in the Description page of Project Settings.

#include "MovingPlatform.h"
#include "Engine.h"


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

	// Set global actor location to actor location.
	GlobalStartLocation = GetActorLocation();
	// Set global target location to the target location.
	GlobalTargetLocation = GetTransform().TransformPosition(TargetLocation);
}

void AMovingPlatform::Tick(float DeltaTime) 
{
	// Override.
	Super::Tick(DeltaTime);

	if (ActiveTriggers > 0)
	{
		// Check whether this is server or not.
		if (HasAuthority())
		{
			// Get actor location.
			FVector Location = GetActorLocation();
			// Calculate the direction.
			float JourneyLength = (GlobalTargetLocation - GlobalStartLocation).Size();
			float JourneyTravelled = (Location - GlobalStartLocation).Size();

			if (JourneyTravelled >= JourneyLength)
			{
				FVector GlobalStartLocationTemp = GlobalStartLocation;
				GlobalStartLocation = GlobalTargetLocation;
				GlobalTargetLocation = GlobalStartLocationTemp;
			}

			FVector Direction = (GlobalTargetLocation - GlobalStartLocation).GetSafeNormal();
			// Move the actor (static).
			// Location += FVector(Speed * DeltaTime, 0, 0);
			// Move the actor (dynamic).
			Location += Speed * DeltaTime * Direction;
			SetActorLocation(Location);
		}
	}	
}

void AMovingPlatform::AddActiveTrigger()
{
	ActiveTriggers++;
	UE_LOG(LogTemp, Warning, TEXT("asd: %i"), ActiveTriggers);
}

void AMovingPlatform::RemoveActiveTrigger()
{
	if (ActiveTriggers > 0)
	{
		ActiveTriggers--;
		UE_LOG(LogTemp, Warning, TEXT("asd: %i"), ActiveTriggers);
	}
}