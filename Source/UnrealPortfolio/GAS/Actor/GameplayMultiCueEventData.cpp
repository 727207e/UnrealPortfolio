// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Actor/GameplayMultiCueEventData.h"
#include "Net/UnrealNetwork.h"
#include "defines/UPServerLogDefine.h"

AGameplayMultiCueEventData::AGameplayMultiCueEventData()
{
	bReplicates = true;
	bNetLoadOnClient = true;
	bAlwaysRelevant = true;
}

void AGameplayMultiCueEventData::OnRep_SpawnLocations()
{
}

void AGameplayMultiCueEventData::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AGameplayMultiCueEventData, SpawnLocations);
}
