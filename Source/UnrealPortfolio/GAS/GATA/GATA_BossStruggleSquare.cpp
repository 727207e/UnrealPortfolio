// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/GATA/GATA_BossStruggleSquare.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GAS/Actor/GameplaySkillEventDataRequest.h"
#include "Components/DecalComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/Actor.h"

AGATA_BossStruggleSquare::AGATA_BossStruggleSquare()
{
	bIsDrawDecal = true;
}

void AGATA_BossStruggleSquare::BeginPlay()
{
	Super::BeginPlay();
}

void AGATA_BossStruggleSquare::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult)
{
	return;
}

void AGATA_BossStruggleSquare::DrawDecal()
{
	Super::DrawDecal();

	Box->SetRelativeLocation(BoxOffsetValue);
}

void AGATA_BossStruggleSquare::GetAttributeSetting()
{
	BoxSizeX = BoxSizeValue.X;
	BoxSizeY = BoxSizeValue.Y;
	BoxSizeZ = BoxSizeValue.Z;
}

void AGATA_BossStruggleSquare::StartTargeting()
{
	FTimerHandle DeadTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(DeadTimerHandle, FTimerDelegate::CreateLambda([&]
		{
			SearchAllTarget();
			Destroy();

		}), DestroyTATime, false);
}

void AGATA_BossStruggleSquare::SearchAllTarget()
{
	FGameplayAbilityTargetDataHandle DataHandle;

	ACharacter* Character = CastChecked<ACharacter>(SourceActor);
	FCollisionShape BoxShape = FCollisionShape::MakeBox(Box->GetScaledBoxExtent());
	TArray<FOverlapResult> OverlapResults;
	FCollisionObjectQueryParams ObjectParams(ECC_Pawn);

	FVector TargetPosition = Box->GetComponentTransform().GetLocation();
	FQuat TargetQuat = Box->GetForwardVector().ToOrientationQuat();

	bool bHasCollision = GetWorld()->OverlapMultiByObjectType(OverlapResults, TargetPosition, TargetQuat, ObjectParams, BoxShape);

	TSet<TWeakObjectPtr<AActor>> InTargetObjects;
	if (bHasCollision)
	{
		for (const FOverlapResult& OverlapResult : OverlapResults)
		{
			ACharacter* OverlapCharacter = Cast<ACharacter>(OverlapResult.GetActor());

			if (OverlapCharacter != Character)
			{
				InTargetObjects.Add(OverlapResult.GetActor());
			}
		}
	}

	FGameplayAbilityTargetData_ActorArray* TargetData = new FGameplayAbilityTargetData_ActorArray();
	TargetData->TargetActorArray = InTargetObjects.Array();
	DataHandle.Add(TargetData);

#if ENABLE_DRAW_DEBUG

	DrawDebugBox(GetWorld(), TargetPosition, Box->GetScaledBoxExtent(), TargetQuat, FColor::Red, false, 2.0f);

#endif

	FTransform TargetTransform(TargetQuat, TargetPosition);
	SpawnGC(TargetTransform);

	TargetDataReadyDelegate.Broadcast(DataHandle);
}

void AGATA_BossStruggleSquare::SpawnGC(FTransform TargetTransform)
{
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(SourceActor);
	if (!TargetASC)
	{
		return;
	}

	float HalfExtentY = Box->GetScaledBoxExtent().Y;
	for (float y = -HalfExtentY; y <= HalfExtentY; y += GCPoisionOffset)
	{
		FVector LocalPoint(0.0f, y, 0.0f);
		FVector WorldPoint = TargetTransform.TransformPosition(LocalPoint);

		FGameplayCueParameters CueParam;
		CueParam.Location = WorldPoint;

		TargetASC->ExecuteGameplayCue(CurrentData->ActionGC, CueParam);

#if ENABLE_DRAW_DEBUG

		DrawDebugPoint(GetWorld(), WorldPoint, 5.0f, FColor::Red, false, 1.0f);

#endif
	}

}
