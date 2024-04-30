// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Attribute/UPMainCharacterAttributeSet.h"

#include "UPGameSingleton.h"
#include "Data/DataAsset/MainCharacter/UPMainCharacterClassTable.h"

UUPMainCharacterAttributeSet::UUPMainCharacterAttributeSet() 
{
	
}

void UUPMainCharacterAttributeSet::MainCharacterSettingValue(const FUPMainCharacterClassTable& Table)
{
	SetMaxHp(Table.MaxHp);
	SetHp(Table.MaxHp);
	SetAttack(Table.Attack);
	SetAttackRange(Table.AttackRange);
	SetAttackSize(Table.AttackSize);
	SetArmor(Table.Armor);
	SetAttackSpeed(Table.AttackSpeed);
	SetAttackRadius(Table.AttackRadius);
	SetAttackRate(Table.AttackRate);
	SetMovementSpeed(Table.MovementSpeed);
	SetMaxMp(Table.MaxMp);
	SetMp(Table.MaxMp);
	
}

void UUPMainCharacterAttributeSet::InitAttributeSet()
{
	MainCharacterSettingValue(UUPGameSingleton::Get().GetCurrentMainCharacterData());
}