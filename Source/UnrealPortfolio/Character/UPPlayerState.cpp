// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/UPPlayerState.h"
#include "AbilitySystemComponent.h"
#include "Interface/AbilitySystemGetInterface.h"

AUPPlayerState::AUPPlayerState()
{
	ASC = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("ASC"));
}

UAbilitySystemComponent* AUPPlayerState::GetAbilitySystemComponent() const
{
	return nullptr;
}

