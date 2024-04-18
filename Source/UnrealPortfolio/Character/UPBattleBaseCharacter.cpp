// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/UPBattleBaseCharacter.h"
#include "AbilitySystemComponent.h"

AUPBattleBaseCharacter::AUPBattleBaseCharacter()
{
	ASC = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("ASC"));
}

void AUPBattleBaseCharacter::SetDead()
{
}

UAnimMontage* AUPBattleBaseCharacter::GetComboActionMontage()
{
	if (ComboActionMontage)
	{
		return ComboActionMontage;
	}

	return nullptr;
}

UUPComboActionData* AUPBattleBaseCharacter::GetComboActionData() const
{
	return nullptr;
}

UAbilitySystemComponent* AUPBattleBaseCharacter::GetAbilitySystemComponent() const
{
	return ASC;
}

void AUPBattleBaseCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	ASC->InitAbilityActorInfo(this, this);
}