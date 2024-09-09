// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/GATA/GATA_AOERandomAttack.h"
#include "NavigationSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Engine/World.h"
#include "Math/RandomStream.h"
#include "GAS/Attribute/BossDataSet/UPBossSkillAttributeSet.h"
#include "GAS/Actor/GameplaySkillEventDataRequest.h"
#include "GameFramework/Character.h"
#include "Character/UPBattleBaseCharacter.h"
#include "Tag/GameplayTags.h"
#include "defines/UPServerLogDefine.h"
#include "Net/UnrealNetwork.h"

AGATA_AOERandomAttack::AGATA_AOERandomAttack()
{
    SearchingRadius = 500.f;
    NiagaraSize = 3.0f;
    AttackTimeDelay = 6.0f;
    bIsConfirmTargetingAndEnd = false;
    TargetTraceAreaOffset = 80.0f;
    ThisTargetTag = TAG_CHARACTER_SKILL;
    bReplicates = true;
    bNetLoadOnClient = true;
    PrimaryActorTick.bCanEverTick = true;


    static ConstructorHelpers::FObjectFinder<UNiagaraSystem> AOEVisualRef(TEXT("/Script/Niagara.NiagaraSystem'/Game/DownloadAssets/Pack_VFX/VFX_Niagara/Magic_Circle/NS_VFX_Magic_Circle_10_Long.NS_VFX_Magic_Circle_10_Long'"));
    if (AOEVisualRef.Object)
    {
        AOEVisual = AOEVisualRef.Object;
    }

    static ConstructorHelpers::FObjectFinder<UNiagaraSystem> ExploreVisualRef(TEXT("/Script/Niagara.NiagaraSystem'/Game/DownloadAssets/Pack_VFX/VFX_Niagara/VFX_Shockwave/NS_VFX_Shockwave_24.NS_VFX_Shockwave_24'"));
    if (ExploreVisualRef.Object)
    {
        ExploreVisual = ExploreVisualRef.Object;
    }
}

void AGATA_AOERandomAttack::ConfirmTargetingAndContinue()
{
    Super::ConfirmTargetingAndContinue();

    bDestroyOnConfirmation = false;

    RandomTargetLocations = GetRandomRadiusPosition();

    for (int index = 0; index < RandomTargetLocations.Num(); index++)
    {
        UNiagaraComponent* SpawnTarget = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), AOEVisual, RandomTargetLocations[index]);
        SpawnTarget->SetWorldScale3D(FVector(NiagaraSize, NiagaraSize, NiagaraSize));

        FTimerHandle AttackDelayTime;
        FVector TargetPos = RandomTargetLocations[index];
        bool bIsLastAttack = (index == RandomTargetLocations.Num() - 1) ? true : false;

        GetWorld()->GetTimerManager().SetTimer(AttackDelayTime, FTimerDelegate::CreateLambda([this, TargetPos, bIsLastAttack] {
            DeactiveTA();
            }), AttackTimeDelay, false);
    }

    ReplcateSourceActorValue = SourceActor;
    AddAttackEvent();
}

void AGATA_AOERandomAttack::OnAOEAttackArea(FGameplayTag TargetTag)
{
    if (TargetTag != this->ThisTargetTag)
    {
        return;
    }

    AttackArea();
}

void AGATA_AOERandomAttack::OnRep_RandomTargetLocations()
{
    for (int index = 0; index < RandomTargetLocations.Num(); index++)
    {
        UNiagaraComponent* SpawnTarget = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), AOEVisual, RandomTargetLocations[index]);
        SpawnTarget->SetWorldScale3D(FVector(NiagaraSize, NiagaraSize, NiagaraSize));
    }
    AddAttackEvent();
}

void AGATA_AOERandomAttack::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(AGATA_AOERandomAttack, RandomTargetLocations);
    DOREPLIFETIME(AGATA_AOERandomAttack, ReplcateSourceActorValue);
}

FGameplayAbilityTargetDataHandle AGATA_AOERandomAttack::MakeTargetData() const
{
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

void AGATA_AOERandomAttack::AttackArea() const
{
    for (int index = 0; index < RandomTargetLocations.Num(); index++)
    {
        UNiagaraComponent* SpawnTarget = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), ExploreVisual, RandomTargetLocations[index]);
        SpawnTarget->SetWorldScale3D(FVector(NiagaraSize, NiagaraSize, NiagaraSize));

        if (HasAuthority())
        {
            ACharacter* ThisCharacter = CastChecked<ACharacter>(SourceActor);
            FCollisionShape SphereShape = FCollisionShape::MakeSphere(TargetTraceAreaOffset * NiagaraSize);
            FCollisionObjectQueryParams ObjectParams(ECC_Pawn);

            TArray<FOverlapResult> OverlapResults;

            bool bHasCollision = GetWorld()->OverlapMultiByObjectType(OverlapResults, RandomTargetLocations[index], FQuat::Identity, ObjectParams, SphereShape);

            TSet<TWeakObjectPtr<AActor>> LeftObjects;
            if (bHasCollision)
            {
                for (const FOverlapResult& OverlapResult : OverlapResults)
                {
                    ACharacter* OverlapCharacter = Cast<ACharacter>(OverlapResult.GetActor());

                    if (OverlapCharacter != ThisCharacter)
                    {
                        LeftObjects.Add(OverlapResult.GetActor());
                    }
                }
            }

#if ENABLE_DRAW_DEBUG

            DrawDebugSphere(GetWorld(), RandomTargetLocations[index], TargetTraceAreaOffset * NiagaraSize, 12, FColor::Red, false, 1.0f);

#endif


            FGameplayAbilityTargetDataHandle DataHandle;
            FGameplayAbilityTargetData_ActorArray* TargetData = new FGameplayAbilityTargetData_ActorArray();

            TargetData->TargetActorArray = LeftObjects.Array();
            DataHandle.Add(TargetData);

            OnTargetDetect.Broadcast(DataHandle);
        }
    }
}

void AGATA_AOERandomAttack::DeactiveTA() const
{
    AUPBattleBaseCharacter* BattleCharacter = Cast<AUPBattleBaseCharacter>(SourceActor);
    if (BattleCharacter)
    {
        BattleCharacter->OnAttackEffect.Remove(AttackEffectHandle);
    }

    FTimerHandle EndAbilityDelay;
    GetWorld()->GetTimerManager().SetTimer(EndAbilityDelay, FTimerDelegate::CreateLambda([&] {

        FGameplayAbilityTargetDataHandle EndDataHandle;
        TargetDataReadyDelegate.Broadcast(EndDataHandle);
        }), 0.3f, false);
}

void AGATA_AOERandomAttack::AddAttackEvent()
{
    AUPBattleBaseCharacter* BattleCharacter = Cast<AUPBattleBaseCharacter>(SourceActor);
    if (BattleCharacter)
    {
        if (!BattleCharacter->OnAttackEffect.IsBoundToObject(this))
        {
            AttackEffectHandle = BattleCharacter->OnAttackEffect.AddUObject(this, &AGATA_AOERandomAttack::OnAOEAttackArea);
        }
    }

}
