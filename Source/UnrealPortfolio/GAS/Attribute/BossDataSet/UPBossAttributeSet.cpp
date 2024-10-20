// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Attribute/BossDataSet/UPBossAttributeSet.h"
#include "Data/DataAsset//Enemy/UPBossTable.h"

UUPBossAttributeSet::UUPBossAttributeSet()
{
}

void UUPBossAttributeSet::InitAttributeSet()
{
	FUPBossTable NormalTable = GetTableData<FUPBossTable>();

	SettingValue(NormalTable);

	SetFleezeTime(NormalTable.FleezeTime);
}
