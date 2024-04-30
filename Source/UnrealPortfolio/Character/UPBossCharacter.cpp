// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/UPBossCharacter.h"

AUPBossCharacter::AUPBossCharacter()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> CharacterMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/DownloadAssets/SuperZombie2/Mesh/Separate/SK_SuperZombie2_body.SK_SuperZombie2_body'"));
	if (CharacterMeshRef.Object)
	{
		GetMesh()->SetSkeletalMesh(CharacterMeshRef.Object);
	}

	static ConstructorHelpers::FClassFinder<UAnimInstance> CharacterAnimRef(TEXT("/Game/Blueprint/Animation/Enemy/ABP_NormalEnemy.ABP_NormalEnemy_C"));
	if (CharacterAnimRef.Class)
	{
		GetMesh()->SetAnimInstanceClass(CharacterAnimRef.Class);
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> ComboMontageRef(TEXT("/Script/Engine.AnimMontage'/Game/Blueprint/Animation/Enemy/Melee/AM_MeleeEnemyAttack.AM_MeleeEnemyAttack'"));
	if (ComboMontageRef.Object)
	{
		ComboActionMontage = ComboMontageRef.Object;
	}
}

void AUPBossCharacter::BeginPlay()
{
	Super::BeginPlay();
}
