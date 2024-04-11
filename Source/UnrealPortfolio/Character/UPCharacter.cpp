// Copyright Epic Games, Inc. All Rights Reserved.

// Copyright Epic Games, Inc. All Rights Reserved.

#include "UPCharacter.h"

#include "EnhancedInputSubsystems.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "Data/UPCharacterControlData.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Materials/Material.h"
#include "Engine/World.h"

class UUPCharacterControlData;

AUPCharacter::AUPCharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;
	
	

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
	
}

void AUPCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AUPCharacter::SetDead()
{
}

void AUPCharacter::LookTarget(const FVector& TargetLocation)
{
	FVector TargetDirection = TargetLocation - GetActorLocation();
	TargetDirection.Z = 0;

	SetActorRotation(TargetDirection.Rotation());
}

FVector AUPCharacter::GetCurLocation()
{
	return GetActorLocation();
}