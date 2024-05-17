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

void AGATA_BossStruggleSquare::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult)
{
	return;
}

void AGATA_BossStruggleSquare::InitSquareTrace()
{
	Super::InitSquareTrace();

	Box->SetRelativeLocation(BoxOffsetValue);
	Boxs.Add(Box);

	if (AttackCount <= 1)
	{
		AttackCount = 1;
		return;
	}

	for (int32 Index = 1; Index < AttackCount; Index++)
	{
		UBoxComponent* NewBox = DuplicateObject<UBoxComponent>(Box, this);
		if (NewBox)
		{
			NewBox->SetupAttachment(RootComponent);
			NewBox->RegisterComponent();
			AddInstanceComponent(NewBox);

			const TArray<USceneComponent*>& ChildComps = Box->GetAttachChildren();
			for (int32 ChildCompsIndex = 0; ChildCompsIndex < ChildComps.Num(); ChildCompsIndex++)
			{
				USceneComponent* NewChildComp = DuplicateObject(ChildComps[ChildCompsIndex], this);
				if (NewChildComp)
				{
					NewChildComp->SetupAttachment(NewBox);
					NewChildComp->RegisterComponent();
					AddInstanceComponent(NewChildComp);
				}
			}

			Boxs.Add(NewBox);
		}
	}

	int32 OffsetResultValue = 0;
	if (AttackCount % 2 == 0)
	{
		for (int32 Index = 0; Index < Boxs.Num(); Index++)
		{
			if (Index < AttackCount / 2)
			{
				OffsetResultValue = -AttackOffset * (Boxs.Num() / 2 - Index - 1) - (AttackOffset / 2);
			}
			else
			{
				OffsetResultValue = AttackOffset * (Index - Boxs.Num() / 2) + (AttackOffset / 2);
			}

			FVector BoxRelativeLocation = Boxs[Index]->GetRelativeLocation() + FVector(0.0f, OffsetResultValue, 0.0f);
			Boxs[Index]->SetRelativeLocation(BoxRelativeLocation);
		}
	}
	else
	{
		for (int32 Index = 0; Index < Boxs.Num(); Index++)
		{
			OffsetResultValue = -AttackOffset * (Boxs.Num() / 2) + (AttackOffset * Index);
			FVector BoxRelativeLocation = Boxs[Index]->GetRelativeLocation() + FVector(0.0f, OffsetResultValue, 0.0f);
			Boxs[Index]->SetRelativeLocation(BoxRelativeLocation);
		}
	}
}

void AGATA_BossStruggleSquare::GetAttributeSetting()
{
	BoxSizeX = BoxSizeValue.X;
	BoxSizeY = BoxSizeValue.Y;
	BoxSizeZ = BoxSizeValue.Z;
}

void AGATA_BossStruggleSquare::StartTargetingTrace()
{
	TArray<UDecalComponent*> DecalComponents;
	GetComponents(DecalComponents);
	for (UDecalComponent* TheDecal : DecalComponents)
	{
		TheDecal->SetVisibility(false);
	}
		
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
	TArray<FOverlapResult> OverlapResults;
	FCollisionObjectQueryParams ObjectParams(ECC_Pawn);
	TSet<TWeakObjectPtr<AActor>> InTargetObjects;

	for (UBoxComponent* TheBox : Boxs)
	{
		FCollisionShape BoxShape = FCollisionShape::MakeBox(TheBox->GetScaledBoxExtent());
		FVector TargetPosition = TheBox->GetComponentTransform().GetLocation();
		FQuat TargetQuat = TheBox->GetForwardVector().ToOrientationQuat();

		bool bHasCollision = GetWorld()->OverlapMultiByObjectType(OverlapResults, TargetPosition, TargetQuat, ObjectParams, BoxShape);

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

		FTransform TargetTransform(TargetQuat, TargetPosition);
		SpawnGC(TargetTransform);

#if ENABLE_DRAW_DEBUG

		DrawDebugBox(GetWorld(), TargetPosition, TheBox->GetScaledBoxExtent(), TargetQuat, FColor::Red, false, 2.0f);

#endif
	}

	FGameplayAbilityTargetData_ActorArray* TargetData = new FGameplayAbilityTargetData_ActorArray();
	TargetData->TargetActorArray = InTargetObjects.Array();
	DataHandle.Add(TargetData);

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
		CueParam.RawMagnitude = 5.0f;

		TargetASC->ExecuteGameplayCue(CurrentData->ActionGC, CueParam);

#if ENABLE_DRAW_DEBUG

		DrawDebugPoint(GetWorld(), WorldPoint, 5.0f, FColor::Red, false, 1.0f);

#endif
	}
}