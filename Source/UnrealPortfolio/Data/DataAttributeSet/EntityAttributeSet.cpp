// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/DataAttributeSet/EntityAttributeSet.h"
#include "GameplayEffectExtension.h"

UEntityAttributeSet::UEntityAttributeSet()
{
}

void UEntityAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	if (Attribute == GetHpAttribute())
	{
		NewValue = NewValue < 0.0f ? 0.0f : NewValue;
	}
}

bool UEntityAttributeSet::PreGameplayEffectExecute(FGameplayEffectModCallbackData& Data)
{
	return Super::PreGameplayEffectExecute(Data);
}

void UEntityAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
}

void UEntityAttributeSet::InitAttributeSet()
{
	InitFromMetaDataTable(BaseStat);
}
