// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/GATA/GATA_HalfCircleTrace.h"
#include "Abilities/GameplayAbility.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GAS/Actor/GameplaySkillEventDataRequest.h"
#include "Data/DataAttributeSet/BossDataSet/UPBossSkillAttributeSet.h"
#include "Character/UPMainCharacter.h"
#include "defines/UPCollision.h"
#include "GameFramework/Character.h"

AGATA_HalfCircleTrace::AGATA_HalfCircleTrace()
{
	bReplicates = true;
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