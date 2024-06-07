// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Attribute/UPMainCharacterAttributeSet.h"
#include "Game/UPGameSingleton.h"
#include "Data/DataAsset/MainCharacter/UPMainCharacterClassTable.h"
#include "Net/UnrealNetwork.h"

UUPMainCharacterAttributeSet::UUPMainCharacterAttributeSet() 
{
	
}

void UUPMainCharacterAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
	if (Attribute == GetMpAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f,GetMaxMp());
	}
}

void UUPMainCharacterAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION_NOTIFY(UUPMainCharacterAttributeSet, Mp, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UUPMainCharacterAttributeSet, MaxMp, COND_None, REPNOTIFY_Always);
}

void UUPMainCharacterAttributeSet::MainCharacterSettingValue(const FUPMainCharacterClassTable& Table)
{
	SetMaxHp(Table.MaxHp);
	SetHp(Table.MaxHp);
	SetAttack(Table.Attack);
	SetAttackRange(Table.AttackRange);
	SetArmor(Table.Armor);
	SetAttackSpeed(Table.AttackSpeed);
	SetAttackRadius(Table.AttackRadius);
	SetAttackRate(Table.AttackRate);
	SetMovementSpeed(Table.MovementSpeed);
	SetMaxMp(Table.MaxMp);
	SetMp(Table.MaxMp);
}

void UUPMainCharacterAttributeSet::OnRep_MaxMp(const FGameplayAttributeData& OldMaxMp)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UUPMainCharacterAttributeSet, MaxMp, OldMaxMp);
}

void UUPMainCharacterAttributeSet::OnRep_Mp(const FGameplayAttributeData& OldMp)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UUPMainCharacterAttributeSet, Mp, OldMp);
}

void UUPMainCharacterAttributeSet::InitAttributeSet()
{
	MainCharacterSettingValue(UUPGameSingleton::Get().GetCurrentMainCharacterData());
}
