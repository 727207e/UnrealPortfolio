// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/UPStrugglingBoss.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AbilitySystemComponent.h"


AUPStrugglingBoss::AUPStrugglingBoss()
{
	ASC = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("ASC"));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> CharacterMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/DownloadAssets/DemonessBoss/Mesh/SK_DemonessBoss.SK_DemonessBoss'"));
	if (CharacterMeshRef.Object)
	{
		GetMesh()->SetSkeletalMesh(CharacterMeshRef.Object);
	}

	static ConstructorHelpers::FClassFinder<UAnimInstance> CharacterAnimRef(TEXT("/Game/Blueprint/Animation/Enemy/Boss/Struggle/ABP_BossDummyStruggle.ABP_BossDummyStruggle_C"));
	if (CharacterAnimRef.Class)
	{
		GetMesh()->SetAnimInstanceClass(CharacterAnimRef.Class);
	}

	StartDelay = 2.0f;
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	GetCharacterMovement()->GravityScale = 0.0f;
	StrugglePatern = { 1, 2, 3, 2, 4, 5, 6, 7 };
	PaternIndex = -1;
}

void AUPStrugglingBoss::StartPatern()
{
	FTimerHandle StartDelayHandle;
	GetWorld()->GetTimerManager().SetTimer(StartDelayHandle, FTimerDelegate::CreateLambda([&]
		{
			PaternIndex++;
			if (PaternIndex >= StrugglePatern.Num())
			{
				PaternIndex = StrugglePatern.Num() - 1;
			}

			OnSkill(StrugglePatern[PaternIndex] - 1);
		}), StartDelay, true, StartDelay);
}

void AUPStrugglingBoss::Hit(FVector TargetLocation, TObjectPtr<class AGameplayEventDataRequest> ActionData)
{
}