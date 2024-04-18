// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/UPEnemyCharacter.h"
#include "AbilitySystemComponent.h"

AUPEnemyCharacter::AUPEnemyCharacter()
{
	
}

void AUPEnemyCharacter::SetDead()
{
	Super::SetDead();
}
//비긴 시작전
void AUPEnemyCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
}
