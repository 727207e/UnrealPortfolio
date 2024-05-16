// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/GATA/GATA_BossStruggleSquare.h"
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

void AGATA_BossStruggleSquare::GetAttributeSetting()
{
	BoxSizeX = BoxSizeXValue;
	BoxSizeY = BoxSizeYValue;
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

	bool bHasCollision = GetWorld()->OverlapMultiByObjectType(OverlapResults, GetActorLocation(), Box->GetComponentQuat(), ObjectParams, BoxShape);

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

	DrawDebugBox(GetWorld(), GetActorLocation(), Box->GetScaledBoxExtent(),FColor::Red, false, 2.0f);

#endif

	TargetDataReadyDelegate.Broadcast(DataHandle);
}
