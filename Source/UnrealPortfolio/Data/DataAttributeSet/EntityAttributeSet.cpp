// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/DataAttributeSet/EntityAttributeSet.h"
#include "Engine/DataTable.h"
#include "Data/DataAsset/UPBaseTable.h"
#include "GameplayEffectExtension.h"
#include "Tag/GameplayTags.h"

UEntityAttributeSet::UEntityAttributeSet()
{
}

void UEntityAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	if (Attribute == GetHpAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f,GetMaxHp());
	}
}

bool UEntityAttributeSet::PreGameplayEffectExecute(FGameplayEffectModCallbackData& Data)
{
	return Super::PreGameplayEffectExecute(Data);
}

void UEntityAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if((GetHp() <= 0.0f) && !bOutOfHp)
	{
		Data.Target.AddLooseGameplayTag(TAG_CHARACTER_ISDEAD);
		OnDead.Broadcast();
	}

	bOutOfHp = (GetHp() <= 0.0f);
}

void UEntityAttributeSet::InitAttributeSet()
{
	SettingValue(GetTableData<FUPBaseTable>());
}
