// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/UPMeleeEnemyCharacter.h"
#include "Components/SkeletalMeshComponent.h"

AUPMeleeEnemyCharacter::AUPMeleeEnemyCharacter()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> CharacterMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/DownloadAssets/SuperZombie2/Mesh/Separate/SK_SuperZombie2_body.SK_SuperZombie2_body'"));
	if (CharacterMeshRef.Object)
	{
		GetMesh()->SetSkeletalMesh(CharacterMeshRef.Object);
	}

	BeltMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Belt"));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> BeltMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/DownloadAssets/SuperZombie2/Mesh/Separate/SK_SuperZombie2_belt.SK_SuperZombie2_belt'"));
	if (BeltMeshRef.Object)
	{
		BeltMesh->SetupAttachment(GetMesh());
		BeltMesh->SetSkeletalMesh(BeltMeshRef.Object);
	}

	TrousersMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Trousers"));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> TrousersMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/DownloadAssets/SuperZombie2/Mesh/Separate/SK_SuperZombie2_trousers.SK_SuperZombie2_trousers'"));
	if (BeltMeshRef.Object)
	{
		TrousersMesh->SetupAttachment(GetMesh());
		TrousersMesh->SetSkeletalMesh(TrousersMeshRef.Object);
	}

	static ConstructorHelpers::FClassFinder<UAnimInstance> CharacterAnimRef(TEXT("/Game/Blueprint/Animation/Enemy/ABP_MeleeEnemy.ABP_MeleeEnemy_C"));
	if (CharacterAnimRef.Class)
	{
		GetMesh()->SetAnimInstanceClass(CharacterAnimRef.Class);
		BeltMesh->SetAnimInstanceClass(CharacterAnimRef.Class);
		TrousersMesh->SetAnimInstanceClass(CharacterAnimRef.Class);
	}
}