// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Attribute/BossDataSet/UPBossSkillAttributeSet.h"
#include "Engine/DataTable.h"
#include "Data/DataAsset/Enemy/UPBossSkillTable.h"
#include "GameplayEffectExtension.h"
#include "Tag/GameplayTags.h"



UUPBossSkillAttributeSet::UUPBossSkillAttributeSet()
{
}

void UUPBossSkillAttributeSet::InitAttributeSet(int32 CurPhaseNumber)
{
	SettingValue(GetTableData<FUPBossSkillTable>(CurPhaseNumber));
}
