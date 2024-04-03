// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/UPEnemyCharacter.h"
#include "AbilitySystemComponent.h"

AUPEnemyCharacter::AUPEnemyCharacter()
{
	ASC = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("ASC"));
}

void AUPEnemyCharacter::SetDead()
{
}

UAbilitySystemComponent* AUPEnemyCharacter::GetAbilitySystemComponent() const
{
	return ASC;
}

void AUPEnemyCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	ASC->InitAbilityActorInfo(this, this);
}