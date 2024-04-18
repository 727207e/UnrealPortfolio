// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/DataAttributeSet/EnemyDataSet/NormalEnemy/MeleeEnemyAttributeSet.h"
#include "GameplayEffectExtension.h"

UMeleeEnemyAttributeSet::UMeleeEnemyAttributeSet() :
	MyAttackKnockback(0.0f),
	MyBodyFreezeTime(0.0f),
	TargetSearchRange(0.0f),
	AttackRadius(0.0f),
	AttackRange(0.0f),
	AttackSpeed(0.0f)
{
	InitHealth(GetMaxHealth());
}

void UMeleeEnemyAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
}

bool UMeleeEnemyAttributeSet::PreGameplayEffectExecute(FGameplayEffectModCallbackData& Data)
{
	if (!Super::PreGameplayEffectExecute(Data))
	{
		return false;
	}

	return true;
}

void UMeleeEnemyAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
}