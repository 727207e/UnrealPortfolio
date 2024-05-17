// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/GATA/GATA_BossStruggleSquare.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GAS/Actor/GameplaySkillEventDataRequest.h"
#include "GAS/Actor/GameplayMultiCueEventData.h"
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
	ACharacter* SourceCharacter = CastChecked<ACharacter>(SourceActor);
	USkeletalMeshComponent* SkeletalMeshComponent = SourceCharacter->GetMesh();
	if (!SkeletalMeshComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("AGATA_BossStruggleSquare : Skeletal mesh component not found."));
		return;
	}

	if (!SkeletalMeshComponent->DoesSocketExist(CurrentData->TargetGenName))
	{
		UE_LOG(LogTemp, Error, TEXT("AGATA_BossStruggleSquare : Skeletal mesh component not found."));
		return;
	}

	FVector NewLocation = SkeletalMeshComponent->GetSocketLocation(CurrentData->TargetGenName);
	FRotator NewRotation = SourceCharacter->GetActorRightVector().ToOrientationRotator();

	SetActorLocationAndRotation(NewLocation, NewRotation);
	
	TArray<TObjectPtr<USceneComponent>> ChildComps;
	RootComponent->GetChildrenComponents(true, ChildComps);

	for (TObjectPtr<USceneComponent> ChildComp : ChildComps)
	{
		if (TObjectPtr<UBoxComponent> BoxComp = Cast<UBoxComponent>(ChildComp))
		{
			Boxs.Add(BoxComp);
		}
	}

	TArray<FTransform> SpawnTransformArray;
	
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = GetInstigator();
	GameplayMultiCueEventData = GetWorld()->SpawnActor<AGameplayMultiCueEventData>(AGameplayMultiCueEventData::StaticClass(), SpawnParams);

	for (TObjectPtr<UBoxComponent> TheBox : Boxs)
	{
		FTransform CurrentBoxTransform = TheBox->GetRelativeTransform();
		CurrentBoxTransform.SetScale3D(FVector(BoxSizeX, BoxSizeY, BoxSizeZ));
		CurrentBoxTransform.SetLocation(CurrentBoxTransform.GetLocation() + BoxOffsetValue);
		TheBox->SetRelativeTransform(CurrentBoxTransform);


		FVector TargetPosition = TheBox->GetComponentTransform().GetLocation();
		FQuat TargetQuat = TheBox->GetForwardVector().ToOrientationQuat();

		FTransform TargetTransform(TargetQuat, TargetPosition);
		SpawnTransformArray.Add(TargetTransform);
	}

	TArray<FVector> AllLocation;
	for (FTransform TargetTransform : SpawnTransformArray)
	{
		float HalfExtentY = Box->GetScaledBoxExtent().Y;
		for (float y = -HalfExtentY; y <= HalfExtentY; y += GCPoisionOffset)
		{
			FVector LocalPoint(0.0f, y, 0.0f);
			FVector WorldPoint = TargetTransform.TransformPosition(LocalPoint);
			AllLocation.Add(WorldPoint);
#if ENABLE_DRAW_DEBUG

			DrawDebugPoint(GetWorld(), WorldPoint, 5.0f, FColor::Red, false, 1.0f);

#endif
		}
	}
	GameplayMultiCueEventData->SpawnLocations = AllLocation;


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

#if ENABLE_DRAW_DEBUG

		DrawDebugBox(GetWorld(), TargetPosition, TheBox->GetScaledBoxExtent(), TargetQuat, FColor::Red, false, 2.0f);

#endif
	}

	SpawnGC();

	FGameplayAbilityTargetData_ActorArray* TargetData = new FGameplayAbilityTargetData_ActorArray();
	TargetData->TargetActorArray = InTargetObjects.Array();
	DataHandle.Add(TargetData);

	TargetDataReadyDelegate.Broadcast(DataHandle);
}

void AGATA_BossStruggleSquare::SpawnGC()
{
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(SourceActor);
	if (!TargetASC)
	{
		return;
	}

	FGameplayCueParameters CueParam;
	CueParam.Instigator = GameplayMultiCueEventData;
	CueParam.RawMagnitude = 5.0f;

	TargetASC->ExecuteGameplayCue(CurrentData->ActionGC, CueParam);

}