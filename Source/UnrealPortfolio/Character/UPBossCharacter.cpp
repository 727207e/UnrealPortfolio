// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/UPBossCharacter.h"
#include "AI/UPBossAIController.h"

AUPBossCharacter::AUPBossCharacter()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> CharacterMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/DownloadAssets/DemonessBoss/Mesh/SK_DemonessBoss.SK_DemonessBoss'"));
	if (CharacterMeshRef.Object)
	{
		GetMesh()->SetSkeletalMesh(CharacterMeshRef.Object);
	}

	static ConstructorHelpers::FClassFinder<UAnimInstance> CharacterAnimRef(TEXT("/Game/Blueprint/Animation/Enemy/Boss/ABP_BossEnemy.ABP_BossEnemy_C"));
	if (CharacterAnimRef.Class)
	{
		GetMesh()->SetAnimInstanceClass(CharacterAnimRef.Class);
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> ComboMontageRef(TEXT("/Script/Engine.AnimMontage'/Game/Blueprint/Animation/Enemy/Boss/AM_BossNormalAttack.AM_BossNormalAttack'"));
	if (ComboMontageRef.Object)
	{
		ComboActionMontage = ComboMontageRef.Object;
	}

	AIControllerClass = AUPBossAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	AttackDelayTime = 5;

}

void AUPBossCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AUPBossCharacter::CounterAttackHit()
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	AnimInstance->Montage_Play(GroggyMontage, 0.3f);
}
