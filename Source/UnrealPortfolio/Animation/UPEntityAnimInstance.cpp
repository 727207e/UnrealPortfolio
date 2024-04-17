// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/UPEntityAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UUPEntityAnimInstance::UUPEntityAnimInstance()
{
	MovingThreshould = 3.0f;
}

void UUPEntityAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Owner = Cast<ACharacter>(GetOwningActor());
	if (Owner)
	{
		Movement = Owner->GetCharacterMovement();
	}
}