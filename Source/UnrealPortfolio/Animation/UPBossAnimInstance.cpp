// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/UPBossAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"

void UUPBossAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (Movement)
	{
		Velocity = Movement->Velocity;
		GroundSpeed = Velocity.Size2D();
		bIsIdle = GroundSpeed < MovingThreshould;
	}
}
