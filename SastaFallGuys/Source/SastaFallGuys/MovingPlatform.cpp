// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetActorLocation();

	FString Name = GetName();

	UE_LOG(LogTemp, Display, TEXT("BeginPlay: %s"), *Name);

}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MovePlatform(DeltaTime);
	
	RotatePlatform(DeltaTime);
}

void AMovingPlatform::MovePlatform(float DeltaTime)
{
	
	// If condition to reverse direction of the platform
	if(ShouldPlatformReturn())
	{
		// Calcuates the distance where a switch in direction is needed and sets the new location there.
		FVector MoveDirection = PlatformVelocity.GetSafeNormal();
		StartLocation += MoveDirection * AllowedDistance;
		SetActorLocation(StartLocation);

		PlatformVelocity *= -1;
	}
	else
	{
		// Gets the current location of platform
		FVector CurrentLocation = GetActorLocation();

		// Update the location of the platform
		CurrentLocation += PlatformVelocity*DeltaTime;
		SetActorLocation(CurrentLocation);

	}
	
}

void AMovingPlatform::RotatePlatform(float DeltaTime)
{
	AddActorLocalRotation(RotationVelocity*DeltaTime);
}

bool AMovingPlatform::ShouldPlatformReturn() const
{
	return GetDistanceMoved() > AllowedDistance;
}

float AMovingPlatform::GetDistanceMoved() const
{
	return FVector::Dist(StartLocation, GetActorLocation());
}