// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/UPRangedEnemyCharacter.h"
#include "Components/CapsuleComponent.h"

AUPRangedEnemyCharacter::AUPRangedEnemyCharacter()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> CharacterMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/DownloadAssets/SuperZombie2/Mesh/SK_SuperZombie2.SK_SuperZombie2'"));
	if (CharacterMeshRef.Object)
	{
		GetMesh()->SetSkeletalMesh(CharacterMeshRef.Object);
	}

	static ConstructorHelpers::FClassFinder<UAnimInstance> CharacterAnimRef(TEXT("/Game/Blueprint/Animation/Enemy/ABP_NormalEnemy.ABP_NormalEnemy_C"));
	if (CharacterAnimRef.Class)
	{
		GetMesh()->SetAnimInstanceClass(CharacterAnimRef.Class);
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> ComboMontageRef(TEXT("/Script/Engine.AnimMontage'/Game/Blueprint/Animation/Enemy/Ranged/AM_RangedAttack.AM_RangedAttack'"));
	if (ComboMontageRef.Object)
	{
		ComboActionMontage = ComboMontageRef.Object;
	}
}

void AUPRangedEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AUPRangedEnemyCharacter::SetDead()
{
	if (GetMesh())
	{
		MeshSetSimulatePhysics(GetMesh(), GetCapsuleComponent());
	}
}