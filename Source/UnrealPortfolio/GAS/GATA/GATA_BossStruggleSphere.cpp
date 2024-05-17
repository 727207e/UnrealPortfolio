// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/GATA/GATA_BossStruggleSphere.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Components/DecalComponent.h"
#include "GameFramework/Character.h"
#include "Game/BossManager.h"
#include "Game/UPGameInstance.h"
#include "GameFramework/Actor.h"
#include "Tag/GameplayTags.h"

AGATA_BossStruggleSphere::AGATA_BossStruggleSphere()
{
	bIsDrawDecal = true;
	bIsAttackSpotActorLocation = true;
}

void AGATA_BossStruggleSphere::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult)
{
	return;
}

void AGATA_BossStruggleSphere::SearchAllTarget()
{
	FGameplayAbilityTargetDataHandle DataHandle;

	ACharacter* Character = CastChecked<ACharacter>(SourceActor);
	TArray<FOverlapResult> OverlapResults;
	FCollisionObjectQueryParams ObjectParams(ECC_Pawn);
	TSet<TWeakObjectPtr<AActor>> InTargetObjects;

	FCollisionShape SphereShape = FCollisionShape::MakeSphere(SphereRadius * SphereScale);
	FVector TargetPosition = SourceActor->GetActorLocation();
	if(!bIsAttackSpotActorLocation)
	{
		ABossManager* BossManager = Cast<UUPGameInstance>(GetGameInstance())->GetBossManager();
		TargetPosition = BossManager->GenPosition->GetActorLocation();
	}
	FQuat TargetQuat = SourceActor->GetActorForwardVector().ToOrientationQuat();

	bool bHasCollision = GetWorld()->OverlapMultiByObjectType(OverlapResults, TargetPosition, TargetQuat, ObjectParams, SphereShape);

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

	SpawnGC(TargetPosition);

#if ENABLE_DRAW_DEBUG

	DrawDebugSphere(GetWorld(), TargetPosition, SphereRadius * SphereScale, 8, FColor::Red, false, 2.0f);

#endif

	FGameplayAbilityTargetData_ActorArray* TargetData = new FGameplayAbilityTargetData_ActorArray();
	TargetData->TargetActorArray = InTargetObjects.Array();
	DataHandle.Add(TargetData);

	TargetDataReadyDelegate.Broadcast(DataHandle);
}

void AGATA_BossStruggleSphere::GetAttributeSetting()
{
	SphereScale = SphereScaleValue;
}

void AGATA_BossStruggleSphere::StartTargeting()
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

void AGATA_BossStruggleSphere::InitTrace()
{
	Super::InitTrace();

	ABossManager* BossManager = Cast<UUPGameInstance>(GetGameInstance())->GetBossManager();
	SetActorLocation(BossManager->GenPosition->GetActorLocation());
}

void AGATA_BossStruggleSphere::SpawnGC(FVector TargetSpawnLocation)
{
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(SourceActor);
	if (!TargetASC)
	{
		return;
	}

	FGameplayCueParameters CueParam;
	CueParam.Location = TargetSpawnLocation;
	CueParam.RawMagnitude = FireBuffSize;
	TargetASC->ExecuteGameplayCue(TAG_FIREBUFF, CueParam);

	CueParam.RawMagnitude = HitGroundSize;
	TargetASC->ExecuteGameplayCue(TAG_HITGROUND, CueParam);
}