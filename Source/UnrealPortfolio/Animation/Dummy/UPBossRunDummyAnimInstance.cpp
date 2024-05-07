// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/Dummy/UPBossRunDummyAnimInstance.h"
#include "GameFramework/Character.h"

UUPBossRunDummyAnimInstance::UUPBossRunDummyAnimInstance()
{
	AnimIndex = 0;
	Velocity = 1.0f;
}

void UUPBossRunDummyAnimInstance::NativeBeginPlay()
{
	FTimerHandle WaitTimer;
	GetWorld()->GetTimerManager().SetTimer(WaitTimer, this, &UUPBossRunDummyAnimInstance::MontageSetting, 1.0f, false);
}

void UUPBossRunDummyAnimInstance::MontageFinish(UAnimMontage* Montage, bool bInterrupted)
{
	AnimIndex++;
	if (AnimationArray[AnimIndex]->GetName() == FlyingName)
	{
		BossDummy = Cast<ACharacter>(TryGetPawnOwner());
		if (!BossDummy)
		{
			UE_LOG(LogTemp, Warning, TEXT("Failed to get character reference in UUPBossRunDummyAnimInstance"));
		}
		else
		{
			FTimerHandle FlyUpTimer;
			GetWorld()->GetTimerManager().SetTimer(FlyUpTimer, this, &UUPBossRunDummyAnimInstance::BossFlyUp, GetWorld()->DeltaTimeSeconds, true);
		}
	}

	else if (AnimIndex < AnimationArray.Num())
	{
		Montage_Play(AnimationArray[AnimIndex]);
	}
}

void UUPBossRunDummyAnimInstance::MontageSetting()
{
	AnimIndex = 0;

	if (AnimationArray.Num() > 0)
	{
		OnMontageEnded.AddDynamic(this, &UUPBossRunDummyAnimInstance::MontageFinish);

		Montage_Play(AnimationArray[AnimIndex]);
	}
}

void UUPBossRunDummyAnimInstance::BossFlyUp()
{
	FVector NewLocation = BossDummy->GetActorLocation() + (FVector(0.0f, 0.0f, 10000.0f) * GetWorld()->DeltaTimeSeconds * Velocity);
	BossDummy->SetActorLocation(NewLocation);
}
