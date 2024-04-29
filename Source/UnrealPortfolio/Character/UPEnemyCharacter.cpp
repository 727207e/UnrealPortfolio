// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/UPEnemyCharacter.h"
#include "AbilitySystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "GAS/State/UPACEntityState.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Components/SkeletalMeshComponent.h"
#include "AI/UPNormalEnemyAIController.h"
#include "Data/DataAttributeSet/EnemyDataSet/NormalEnemy/UPEnemyAttributeSet.h"


AUPEnemyCharacter::AUPEnemyCharacter()
{
	/** Setup Hit Montage **/
	static::ConstructorHelpers::FObjectFinder<UAnimMontage> HitAnimMontageRef(TEXT("/Script/Engine.AnimMontage'/Game/Blueprint/Animation/Enemy/AM_NormalEnemyHit.AM_NormalEnemyHit'"));
	if(HitAnimMontageRef.Object)
	{
		HitMontage = HitAnimMontageRef.Object;
	}

	AIControllerClass = AUPNormalEnemyAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void AUPEnemyCharacter::SetDead()
{
	Super::SetDead();
}

void AUPEnemyCharacter::PreInitializeComponents()
{
	Super::PreInitializeComponents();

	if (EnemyEntityStateType)
	{
		EnemyEntityState = NewObject<UUPACEntityState>(this, EnemyEntityStateType);
		if (EnemyEntityState)
		{
			this->AddOwnedComponent(EnemyEntityState);
			EnemyEntityState->RegisterComponent();
			EnemyEntityState->InitEntityState(this);
		}
	}
}

void AUPEnemyCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (EnemyEntityState && HasAuthority())
	{
		EnemyEntityState->PostInitialize();
	}
}

void AUPEnemyCharacter::MeshSetSimulatePhysics(USkeletalMeshComponent* targetMesh, UCapsuleComponent* targetCapsule)
{
	UE_LOG(LogTemp, Log, TEXT("MeshSetSimulatePhysics"));
	targetMesh->SetCollisionProfileName(TEXT("PhysicsActor"));
	targetMesh->SetAnimInstanceClass(nullptr);
	targetMesh->SetSimulatePhysics(true);

	if (targetCapsule)
	{
		targetCapsule->SetGenerateOverlapEvents(false);
	}
}

void AUPEnemyCharacter::SetupASCHostPlayer(AActor* InOwnerActor)
{
	if (nullptr == EnemyEntityState)
	{
		return;
	}

	ASC = EnemyEntityState->ASC;

	if (HasAuthority())
	{
		Super::SetupASCHostPlayer(InOwnerActor);
	}

	ASC->AddSpawnedAttribute(EnemyEntityState->AttributeSet);
	ASC->InitAbilityActorInfo(InOwnerActor, this);
}

void AUPEnemyCharacter::NormalAttack()
{
	if (bCanAttack)
	{
		CallGAS(0);
		bCanAttack = false;

		UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(this);
		SetAttackDelay(TargetASC->GetSet<UUPEnemyAttributeSet>()->GetAttackRate());
	}
}