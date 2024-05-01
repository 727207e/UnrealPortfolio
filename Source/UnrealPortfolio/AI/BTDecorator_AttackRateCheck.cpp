// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTDecorator_AttackRateCheck.h"
#include "AIController.h"
#include "Character/UPBattleBaseCharacter.h"

UBTDecorator_AttackRateCheck::UBTDecorator_AttackRateCheck()
{
	NodeName = TEXT("CanAttackRate");
}

bool UBTDecorator_AttackRateCheck::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	AUPBattleBaseCharacter* ControllingPawn = Cast<AUPBattleBaseCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == ControllingPawn)
	{
		return false;
	}

	return ControllingPawn->bCanAttack;
}