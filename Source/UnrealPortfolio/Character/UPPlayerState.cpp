// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/UPPlayerState.h"
#include "AbilitySystemComponent.h"
#include "GAS/Attribute/PlayerDataSet/UPMainCharacterAttributeSet.h"


AUPPlayerState::AUPPlayerState()
{
	ASC = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("ASC"));
	AttributeSet = CreateDefaultSubobject<UUPMainCharacterAttributeSet>(TEXT("AttributeSet"));
	ASC->SetIsReplicated(true);
	ASC->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	NetUpdateFrequency = 60;
}

class UAbilitySystemComponent* AUPPlayerState::GetAbilitySystemComponent() const
{
	return ASC;
}

class UEntityAttributeSet* AUPPlayerState::GetMainCharacterAttributeSet() const
{
	return  AttributeSet;
}