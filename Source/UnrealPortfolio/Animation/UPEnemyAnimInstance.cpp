// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/UPEnemyAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UUPEnemyAnimInstance::UUPEnemyAnimInstance()
{

}

void UUPEnemyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (Movement)
	{
		Velocity = Movement->Velocity;
		GroundSpeed = Velocity.Size2D();
		bIsIdle = GroundSpeed < MovingThreshould;
	}
}

void UUPEnemyAnimInstance::SetIsTargetLock(bool IsLockOn)
{
	bIsTargetLock = (uint8)IsLockOn;
}