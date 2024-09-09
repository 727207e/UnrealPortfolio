// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTDecorator_AttackInRange.h"
#include "AIController.h"
#include "Character/UPBattleBaseCharacter.h"
#include "defines/UPAIDefine.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GAS/Attribute/EnemyDataSet/NormalEnemy/UPEnemyAttributeSet.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTDecorator_AttackInRange::UBTDecorator_AttackInRange()
{
	NodeName = TEXT("CanAttackRange");
}

bool UBTDecorator_AttackInRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	AUPBattleBaseCharacter* ControllingPawn = Cast<AUPBattleBaseCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == ControllingPawn)
	{
		return false;
	}

	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(ControllingPawn);
	if (nullptr == TargetASC)
	{
		UE_LOG(LogTemp, Error, TEXT("Enemy Can't Find ASC"));
		return false;
	}

	UUPEnemyAttributeSet* TargetAttribute = const_cast<UUPEnemyAttributeSet*>(TargetASC->GetSet<UUPEnemyAttributeSet>());
	if (nullptr == TargetAttribute)
	{
		UE_LOG(LogTemp, Error, TEXT("Enemy Can't Find AttributeSet"));
		return false;
	}

	APawn* Target = Cast<APawn>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(BBKEY_TARGET));
	if (nullptr == Target)
	{
		return false;
	}

	float DistanceToTarget = ControllingPawn->GetDistanceTo(Target);
	float AttackRangeWithRadius = TargetAttribute->GetAttackRange();
	bResult = (DistanceToTarget <= AttackRangeWithRadius);

	return bResult;
}