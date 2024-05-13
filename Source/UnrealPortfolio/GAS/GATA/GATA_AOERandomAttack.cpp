// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/GATA/GATA_AOERandomAttack.h"
#include "NavigationSystem.h"
#include "Engine/World.h"
#include "Math/RandomStream.h"
#include "Data/DataAttributeSet/BossDataSet/UPBossSkillAttributeSet.h"
#include "GAS/Actor/GameplaySkillEventDataRequest.h"

AGATA_AOERandomAttack::AGATA_AOERandomAttack()
{
    SearchingRadius = 500.f;
}

FGameplayAbilityTargetDataHandle AGATA_AOERandomAttack::MakeTargetData() const
{
    TArray<FVector> RandomLocations = GetRandomRadiusPosition();

#if ENABLE_DRAW_DEBUG

    for (int index = 0; index < RandomLocations.Num(); index++)
    {
        DrawDebugBox(SourceActor->GetWorld(), RandomLocations[index], FVector(20.f, 20.f, 20.f), FColor::Red, true);
    }

#endif

	return FGameplayAbilityTargetDataHandle();
}

TArray<FVector> AGATA_AOERandomAttack::GetRandomRadiusPosition() const
{
    TArray<FVector> RandomLocations;

    UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(SourceActor->GetWorld());
    if (!NavSys)
    {
        UE_LOG(LogTemp, Error, TEXT("GATA_AOERandomAttack Can't Find NavigationSystem"));
        return RandomLocations;
    }

    FRandomStream RandomStream(FMath::Rand());
    int32 AreaCount = CurrentData->TargetAttributeSet->GetAttackNumber();

    for (int32 i = 0; i < AreaCount; ++i)
    {
        FNavLocation RandomLocation;
        if (NavSys->GetRandomPointInNavigableRadius(SourceActor->GetActorLocation(), SearchingRadius, RandomLocation))
        {
            RandomLocations.Add(RandomLocation);
        }
    }

    return RandomLocations;
}
