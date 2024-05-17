// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/GATA/GATA_BossStruggleDoubleSphere.h"
#include "GameFramework/Character.h"

AGATA_BossStruggleDoubleSphere::AGATA_BossStruggleDoubleSphere()
{
}

void AGATA_BossStruggleDoubleSphere::SearchAllTarget()
{
	FGameplayAbilityTargetDataHandle DataHandle;

	ACharacter* Character = CastChecked<ACharacter>(SourceActor);
	FCollisionObjectQueryParams ObjectParams(ECC_Pawn);
	FVector TargetPosition = SourceActor->GetActorLocation();
	FQuat TargetQuat = SourceActor->GetActorForwardVector().ToOrientationQuat();

	TArray<FOverlapResult> OverlapDamageResult;
	TSet<TWeakObjectPtr<AActor>> InTargetObjects;
	FCollisionShape SphereDamageShape = FCollisionShape::MakeSphere(SphereRadius * SphereScale);
	bool bOverlapDamageResult = GetWorld()->OverlapMultiByObjectType(OverlapDamageResult, TargetPosition, TargetQuat, ObjectParams, SphereDamageShape);

	TArray<FOverlapResult> OverlapSafeResult;
	TSet<TWeakObjectPtr<AActor>> InSafeObjects;
	FCollisionShape SphereSafeShape = FCollisionShape::MakeSphere(SphereRadius * InnerSphereScaleValue);
	bool bOverlapSafeResult = GetWorld()->OverlapMultiByObjectType(OverlapSafeResult, TargetPosition, TargetQuat, ObjectParams, SphereSafeShape);

	if (bOverlapDamageResult)
	{
		for (const FOverlapResult& OverlapResult : OverlapDamageResult)
		{
			ACharacter* OverlapCharacter = Cast<ACharacter>(OverlapResult.GetActor());

			if (OverlapCharacter != Character)
			{
				InTargetObjects.Add(OverlapResult.GetActor());
			}
		}

		if (bOverlapSafeResult)
		{
			for (const FOverlapResult& OverlapResult : OverlapSafeResult)
			{
				InSafeObjects.Add(OverlapResult.GetActor());
			}
			
			for (const TWeakObjectPtr<AActor>& SafeObject : InSafeObjects)
			{
				InTargetObjects.Remove(SafeObject);
			}
		}
	}


	FTransform TargetTransform(TargetQuat, TargetPosition);

#if ENABLE_DRAW_DEBUG

	DrawDebugSphere(GetWorld(), TargetPosition, SphereRadius * SphereScale, 8, FColor::Red, false, 4.0f);
	DrawDebugSphere(GetWorld(), TargetPosition, SphereRadius * InnerSphereScaleValue, 8, FColor::Blue, false, 4.0f);

#endif

	FGameplayAbilityTargetData_ActorArray* TargetData = new FGameplayAbilityTargetData_ActorArray();
	TargetData->TargetActorArray = InTargetObjects.Array();
	DataHandle.Add(TargetData);

	TargetDataReadyDelegate.Broadcast(DataHandle);
}
