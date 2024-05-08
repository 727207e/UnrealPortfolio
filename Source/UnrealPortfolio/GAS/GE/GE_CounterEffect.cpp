// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/GE/GE_CounterEffect.h"
#include "Data/DataAttributeSet/EntityAttributeSet.h"
#include "Character/UPBossCharacter.h"
#include "Tag/GameplayTags.h"

void UGE_CounterEffect::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	UAbilitySystemComponent* SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();
	UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();

    if (nullptr == SourceASC || nullptr == TargetASC)
    {
        UE_LOG(LogTemp,Error, TEXT("GU_CounterEffect Can't Find ASC"));
        return;
    }

    if (SourceASC->HasMatchingGameplayTag(TAG_COUNTER_ATTACK) && TargetASC->HasMatchingGameplayTag(TAG_COUNTER_HIT))
    {
        AUPBossCharacter* TargetBoss = Cast<AUPBossCharacter>(TargetASC->GetAvatarActor());
        if (nullptr == TargetBoss)
        {
            UE_LOG(LogTemp, Error, TEXT("GU_CounterEffect Can't Find TargetBoss"));
            return;
        }

        TargetBoss->CounterAttackHit();
    }
}