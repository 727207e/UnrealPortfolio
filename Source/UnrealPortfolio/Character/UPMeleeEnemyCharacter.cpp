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
	
	
	static ConstructorHelpers::FObjectFinder<UAnimMontage> ComboMontageRef(TEXT("/Script/Engine.AnimMontage'/Game/Blueprint/Animation/Enemy/AM_MeleeEnemyAttack.AM_MeleeEnemyAttack'"));
	if (ComboMontageRef.Object)
	{
		ComboActionMontage = ComboMontageRef.Object;
	}
}

void AUPMeleeEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle DeadTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(DeadTimerHandle, this, &AUPMeleeEnemyCharacter::SetDead, 5.0f, false);
}


void AUPMeleeEnemyCharacter::SetDead()
{
	if (GetMesh() && BeltMesh && TrousersMesh)
	{
		//// 새로운 위치로 캐릭터를 이동시킵니다.
		//SetActorLocation(GetCurLocation() + FVector(0,0,500));

		GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		//BeltMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		//TrousersMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

		GetMesh()->SetSimulatePhysics(true);
		//BeltMesh->SetSimulatePhysics(true);
		//TrousersMesh->SetSimulatePhysics(true);
		//GetMesh()->SetAllBodiesSimulatePhysics(true);
	}
}