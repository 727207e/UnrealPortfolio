// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/DataAttributeSet/EnemyDataSet/NormalEnemy/UPEnemyAttributeSet.h"
#include "GameplayEffectExtension.h"

UUPEnemyAttributeSet::UUPEnemyAttributeSet()
{
}

void UUPEnemyAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
}

bool UUPEnemyAttributeSet::PreGameplayEffectExecute(FGameplayEffectModCallbackData& Data)
{
	if (!Super::PreGameplayEffectExecute(Data))
	{
		return false;
	}

	return true;
}

void UUPEnemyAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
}