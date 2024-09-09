// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Attribute/EnemyDataSet/NormalEnemy/UPEnemyAttributeSet.h"
#include "Data/DataAsset/Enemy/UPNormalEnemyTable.h"
#include "Data/DataAsset/UPBaseTable.h"
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

void UUPEnemyAttributeSet::InitAttributeSet()
{
	FUPNormalEnemyTable NormalTable = GetTableData<FUPNormalEnemyTable>();

	SettingValue(NormalTable);

	SetMyAttackKnockback(NormalTable.MyAttackKnockback);
	SetFleezeTime(NormalTable.FleezeTime);
	SetTargetSearchingRange(NormalTable.TargetSearchingRange);
}
