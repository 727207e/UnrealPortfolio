// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/UPStrugglingBoss.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AbilitySystemComponent.h"

// Sets default values
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
}

UAbilitySystemComponent* AUPStrugglingBoss::GetAbilitySystemComponent() const
{
	return ASC;

	GetCharacterMovement()->GravityScale = 0.0f;
}

void AUPStrugglingBoss::Hit(FVector TargetLocation, TObjectPtr<class AGameplayEventDataRequest> ActionData)
{
}