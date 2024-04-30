// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/DataAttributeSet/EntityAttributeSet.h"
#include "Engine/DataTable.h"
#include "Data/DataAsset/UPBaseTable.h"
#include "GameplayEffectExtension.h"

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
}

void UEntityAttributeSet::InitAttributeSet()
{
	SettingValue(GetTableData());
}

void UEntityAttributeSet::SettingValue(FUPBaseTable table)
{
	SetHp(table.MaxHp);
	SetMaxHp(table.MaxHp);
	SetAttack(table.Attack);
	SetAttackRange(table.AttackRange);
	SetAttackSize(table.AttackSize);
	SetArmor(table.Armor);
	SetAttackSpeed(table.AttackSpeed);
	SetAttackRate(table.AttackRate);
	SetAttackRadius(table.AttackRadius);
	SetMovementSpeed(table.MovementSpeed);
}

FUPBaseTable UEntityAttributeSet::GetTableData()
{
	check(BaseStat);
	TArray<FName> RowNames = BaseStat->GetRowNames();
	FUPBaseTable table;
	for (int i = 0; i < RowNames.Num(); ++i)
	{
		if (StatName.Equals(RowNames[i].ToString()))
		{
			table = *(BaseStat->FindRow<FUPBaseTable>(RowNames[i], RowNames[i].ToString()));
			break;
		}
	}

	return table;
}
