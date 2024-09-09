// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/GATA/GATA_HalfCircleTrace.h"
#include "Abilities/GameplayAbility.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GAS/Actor/GameplaySkillEventDataRequest.h"
#include "GAS/Attribute/BossDataSet/UPBossSkillAttributeSet.h"
#include "Character/UPMainCharacter.h"
#include "defines/UPCollision.h"
#include "Engine/DecalActor.h"
#include "GameFramework/Character.h"
#include "Components/SceneComponent.h"
#include "Components/DecalComponent.h"
#include "Components/BoxComponent.h"

AGATA_HalfCircleTrace::AGATA_HalfCircleTrace()
{
	RootSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(RootSceneComponent);

	LeftHalfDecal = CreateDefaultSubobject<UDecalComponent>(TEXT("LeftHalfDecal"));
	LeftHalfDecal->SetupAttachment(RootSceneComponent);
	LeftHalfDecal->SetRelativeRotation(FRotator(0, -90.0f, 0.f));

	bReplicates = true;
	bIsDrawDecal = true;
}

void AGATA_HalfCircleTrace::DrawDecal()
{
	bDestroyOnConfirmation = false;

	FTransform CurrentTransform = GetActorTransform();
	CurrentTransform.SetLocation(SourceActor->GetActorLocation());
	CurrentTransform.SetRotation(SourceActor->GetActorQuat());

	SetActorTransform(CurrentTransform);

	const float AttackRadius = 1000;
	LeftHalfDecal->DecalSize = FVector(AttackRadius/2.0f, AttackRadius/2.0f, AttackRadius/2.0f);

	FTimerHandle StartTarget;
	GetWorld()->GetTimerManager().SetTimer(StartTarget, FTimerDelegate::CreateLambda([&]
		{
			const FGameplayAbilityTargetDataHandle DataHandle = MakeTargetData();
			TargetDataReadyDelegate.Broadcast(DataHandle);
		}), 1.3f, false);
}

FGameplayAbilityTargetDataHandle AGATA_HalfCircleTrace::MakeTargetData() const
{
	FGameplayAbilityTargetDataHandle DataHandle;
	ACharacter* Character = CastChecked<ACharacter>(SourceActor);

	const float AttackRadius = 1000;

	FVector LeftDirection = FVector::CrossProduct(Character->GetActorForwardVector(), FVector::UpVector);
	FCollisionShape SphereShape = FCollisionShape::MakeSphere(AttackRadius);

	TArray<FOverlapResult> OverlapResults; 

	FCollisionObjectQueryParams ObjectParams(ECC_Pawn);

	bool bHasCollision = GetWorld()->OverlapMultiByObjectType(OverlapResults, Character->GetActorLocation(), FQuat::Identity, ObjectParams, SphereShape);

	TSet<TWeakObjectPtr<AActor>> LeftObjects;
	if (bHasCollision)
	{
		for (const FOverlapResult& OverlapResult : OverlapResults)
		{
			ACharacter* OverlapCharacter = Cast<ACharacter>(OverlapResult.GetActor());

			if (OverlapCharacter != Character) 
			{
				FVector ToHitObject = OverlapCharacter->GetActorLocation() - Character->GetActorLocation();
				float DotProduct = FVector::DotProduct(ToHitObject, LeftDirection);
				if (DotProduct > 0)
				{
					LeftObjects.Add(OverlapResult.GetActor());
				}
			}
		}
	}

	FGameplayAbilityTargetData_ActorArray* TargetData = new FGameplayAbilityTargetData_ActorArray();
	TargetData->TargetActorArray = LeftObjects.Array();
	DataHandle.Add(TargetData);

#if ENABLE_DRAW_DEBUG

	DrawDebugSphere(GetWorld(), Character->GetActorLocation(), AttackRadius, 12, FColor::Red, false, 2.0f);

#endif

	return DataHandle;
}