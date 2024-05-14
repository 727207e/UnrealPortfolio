// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/GA/Skill/GA_BossEnemySpawnSkill.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "NavigationSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "AIController.h"
#include "GameFramework/Character.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "defines/UPAIDefine.h"
#include "Data/DataAttributeSet/BossDataSet/UPBossSkillAttributeSet.h"

UGA_BossEnemySpawnSkill::UGA_BossEnemySpawnSkill()
{
	SpawnDelay = 1.0f;
    SearchingRadius = 1000.f;

    static ConstructorHelpers::FObjectFinder<UNiagaraSystem> SpawnVisualRef(TEXT("/Script/Niagara.NiagaraSystem'/Game/DownloadAssets/Pack_VFX/VFX_Niagara/Buffs/NS_Buffs_Buff_11.NS_Buffs_Buff_11'"));
    if (SpawnVisualRef.Object)
    {
        SpawnVisual = SpawnVisualRef.Object;
    }
}

void UGA_BossEnemySpawnSkill::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	FTimerHandle SpawnEnemiesTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(SpawnEnemiesTimerHandle, this, &UGA_BossEnemySpawnSkill::SpawnEnemies, SpawnDelay, false);
}

void UGA_BossEnemySpawnSkill::SpawnEnemies()
{
    TArray<FVector> SpawnArray = GetRandomRadiusPosition();
    int32 TargetEnemyIndex = 0;

    for (int index = 0; index < SpawnArray.Num(); index++)
    {
        UNiagaraComponent* SpawnVisualEffect = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), SpawnVisual, SpawnArray[index]);

        FVector Location = SpawnArray[index];
        Location.Z += 20.0f;
        FRotator Rotation = CurrentActorInfo->AvatarActor->GetActorQuat().Rotator();
        AUPEnemyCharacter* Enemy = GetWorld()->SpawnActor<AUPEnemyCharacter>(EnemyArray[TargetEnemyIndex], Location, Rotation);

        if (nullptr == Enemy)
        {
            UE_LOG(LogTemp, Warning, TEXT("UGA_BossEnemySpawnSkill : BossCharacter And SpawnPosition Overlap. Pass This Spawn"));
            continue;
        }

        SettingTarget(Enemy);

        TargetEnemyIndex++;
        if (TargetEnemyIndex >= EnemyArray.Num())
        {
            TargetEnemyIndex = 0;
        }
    }
}

void UGA_BossEnemySpawnSkill::SettingTarget(ACharacter* TargetEnemy)
{
    if (GetWorld()->GetNumPlayerControllers() == 0)
    {
        UE_LOG(LogTemp, Error, TEXT("GA_BossEnemySpawnSkill : There is No Player"));
        return;
    }

    int32 TargetNumber = FMath::RandRange(0, GetWorld()->GetNumPlayerControllers() - 1);
    APlayerController* TargetPlayerController = nullptr;

    int32 CountNumber = 0;
    for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
    {
        APlayerController* ItPlayerController = Iterator->Get();
        if (ItPlayerController)
        {
            if (CountNumber == TargetNumber)
            {
                TargetPlayerController = ItPlayerController;
                break;
            }
            CountNumber++;
        }
    }

    if (nullptr == TargetPlayerController)
    {
        UE_LOG(LogTemp, Error, TEXT("UGA_BossEnemySpawnSkill : Can't Find Target Random Player Controller"));
        return;
    }

    APawn* RandomPlayer = TargetPlayerController->GetPawn();

    AAIController* AIController = Cast<AAIController>(TargetEnemy->GetController());
    if (AIController && AIController->GetBlackboardComponent())
    {
        AIController->GetBlackboardComponent()->SetValueAsObject(BBKEY_TARGET, RandomPlayer);
    }
}

TArray<FVector> UGA_BossEnemySpawnSkill::GetRandomRadiusPosition()
{
    TArray<FVector> RandomLocations;

    UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(CurrentActorInfo->AvatarActor->GetWorld());
    if (!NavSys)
    {
        UE_LOG(LogTemp, Error, TEXT("GATA_AOERandomAttack Can't Find NavigationSystem"));
        return RandomLocations;
    }

    FRandomStream RandomStream(FMath::Rand());
    int32 AreaCount = SourceAttribute->GetAttackNumber();

    for (int32 i = 0; i < AreaCount * 2; ++i)
    {
        FNavLocation RandomLocation;
        if (NavSys->GetRandomPointInNavigableRadius(CurrentActorInfo->AvatarActor->GetActorLocation(), SearchingRadius, RandomLocation))
        {
            RandomLocations.Add(RandomLocation);
        }
    }

    return RandomLocations;
}