// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/DataAttributeSet/EntityAttributeSet.h"
#include "GameplayEffectExtension.h"

UEntityAttributeSet::UEntityAttributeSet() :
	AttackRate(0.0f),
	MaxAttackRate(0.0f),
	MaxHealth(0.0f),
	Damage(0.0f),
	Defense(0.0f),
	MaxDefense(0.0f)
{
	InitHealth(GetMaxHealth());
}

void UEntityAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxHealth());
	}

	if (Attribute == GetDamageAttribute())
	{
		NewValue = NewValue < 0.0f ? 0.0f : NewValue;
	}
}

bool UEntityAttributeSet::PreGameplayEffectExecute(FGameplayEffectModCallbackData& Data)
{
	if (!Super::PreGameplayEffectExecute(Data))
	{
		return false;
	}

	return true;
}

void UEntityAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
}