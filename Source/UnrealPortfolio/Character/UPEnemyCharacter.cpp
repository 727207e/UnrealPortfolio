// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/UPEnemyCharacter.h"
#include "AbilitySystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "GAS/State/UPACEntityState.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Components/SkeletalMeshComponent.h"
#include "AI/UPEnemyAIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GAS/Attribute/EntityAttributeSet.h"
#include "GAS/GA/Skill/GA_SkillBase.h"


AUPEnemyCharacter::AUPEnemyCharacter()
{
	/** Setup Hit Montage **/
	static::ConstructorHelpers::FObjectFinder<UAnimMontage> HitAnimMontageRef(TEXT("/Script/Engine.AnimMontage'/Game/Blueprint/Animation/Enemy/AM_NormalEnemyHit.AM_NormalEnemyHit'"));
	if (HitAnimMontageRef.Object)
	{
		HitMontage = HitAnimMontageRef.Object;
	}
	static::ConstructorHelpers::FObjectFinder<UAnimMontage> FindTargetMontageRef(TEXT("/Script/Engine.AnimMontage'/Game/Blueprint/Animation/Enemy/AM_NormalEnemyFoundTarget.AM_NormalEnemyFoundTarget'"));
	if (FindTargetMontageRef.Object)
	{
		FindTargetMontage = FindTargetMontageRef.Object;
	}

	AIControllerClass = AUPEnemyAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AttackDelayTime = 3;
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
			EnemyEntityState->AttributeSet->OnDead.AddDynamic(this,&ThisClass::OnDead);
		}
	}
}

void AUPEnemyCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (EnemyEntityState && HasAuthority())
	{
		UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(this);
		if (TargetASC)
		{
			EnemyEntityState->PostInitialize();


			GetCharacterMovement()->MaxWalkSpeed *= TargetASC->GetSet<UEntityAttributeSet>()->GetMovementSpeed();
		}
	}
}

void AUPEnemyCharacter::MeshSetSimulatePhysics(USkeletalMeshComponent* targetMesh, UCapsuleComponent* targetCapsule)
{
	TArray<USkeletalMeshComponent*> singleMeshArray;
	singleMeshArray.Add(targetMesh);

	MeshSetSimulatePhysics(singleMeshArray, targetCapsule);
}

void AUPEnemyCharacter::MeshSetSimulatePhysics(TArray<USkeletalMeshComponent*> targetMeshes, UCapsuleComponent* targetCapsule)
{
	GetController()->UnPossess();

	for (USkeletalMeshComponent* targetMesh : targetMeshes)
	{
		if (targetMesh)
		{
			targetMesh->SetCollisionProfileName(TEXT("PhysicsActor"));
			targetMesh->SetAnimInstanceClass(nullptr);
			targetMesh->SetSimulatePhysics(true);
		}
	}

	if (targetCapsule)
	{
		targetCapsule->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

void AUPEnemyCharacter::SetupASCHostPlayer(AActor* InOwnerActor)
{
	if (nullptr == EnemyEntityState)
	{
		UE_LOG(LogTemp, Error, TEXT("EnemyCharacter No Enemy Entity State"));
		return;
	}

	ASC = EnemyEntityState->ASC;

	if (HasAuthority())
	{
		Super::SetupASCHostPlayer(InOwnerActor);
	}
	ASC->AddSpawnedAttribute(EnemyEntityState->AttributeSet);
	ASC->InitAbilityActorInfo(InOwnerActor, this);
	AttributeSet = EnemyEntityState->AttributeSet;
}

void AUPEnemyCharacter::NormalAttack()
{
	CallGAS(0);
	bCanAttack = false;

	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(this);
	SetAttackDelay(TargetASC->GetSet<UEntityAttributeSet>()->GetAttackRate());
}

void AUPEnemyCharacter::OnSkill(int32 SkillNumber)
{
	Super::OnSkill(SkillNumber);

	bCanAttack = false;
}

FGameplayAbilitySpec AUPEnemyCharacter::FindTarget()
{
	CallGAS(1);
	auto UsingGas = GetUsingGas(1);
	
	if (UsingGas.Num() > 0)
	{
		return UsingGas[0];
	}

	return FGameplayAbilitySpec();
}

void AUPEnemyCharacter::OnFindTargetEnd()
{
	OnEndAnimDelegate.ExecuteIfBound();
}

void AUPEnemyCharacter::SetDelegate(const FOnEndAnimDelegate& OnEndAnim)
{
	OnEndAnimDelegate = OnEndAnim;
}

