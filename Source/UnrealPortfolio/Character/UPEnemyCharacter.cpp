// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/UPEnemyCharacter.h"
#include "AbilitySystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "GAS/State/UPACEntityState.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Components/SkeletalMeshComponent.h"


AUPEnemyCharacter::AUPEnemyCharacter()
{
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
		///////////TEST CODE////////////////
		UE_LOG(LogTemp, Log, TEXT("After Start"));
		UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(this);
		if (TargetASC)
		{
			EnemyEntityState->PostInitialize();

			UEntityAttributeSet* TargetEntityAttribute = const_cast<UEntityAttributeSet*>(TargetASC->GetSet<UEntityAttributeSet>());

			if (TargetEntityAttribute)
			{
				UE_LOG(LogTemp, Log, TEXT("MinusOn, %f"), TargetASC->GetSet<UEntityAttributeSet>()->GetHp());
				TargetEntityAttribute->SetHp(TargetEntityAttribute->GetHp() - 2);

				UE_LOG(LogTemp, Log, TEXT("MinusOn, %f"), TargetASC->GetSet<UEntityAttributeSet>()->GetHp());
			}
		}

		///////////TEST CODE////////////////
	}
}

void AUPEnemyCharacter::MeshSetSimulatePhysics(USkeletalMeshComponent* targetMesh, UCapsuleComponent* targetCapsule)
{
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
