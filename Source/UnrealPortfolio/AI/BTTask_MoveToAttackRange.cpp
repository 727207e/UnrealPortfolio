// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_MoveToAttackRange.h"
#include "AIController.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "defines/UPAIDefine.h"
#include "Data/DataAttributeSet/EnemyDataSet/NormalEnemy/UPEnemyAttributeSet.h"


UBTTask_MoveToAttackRange::UBTTask_MoveToAttackRange()
{
	
}

EBTNodeResult::Type UBTTask_MoveToAttackRange::PerformMoveTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AActor* CurActor = OwnerComp.GetAIOwner()->GetPawn();

	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(CurActor);
	if (nullptr == TargetASC)
	{
		UE_LOG(LogTemp, Error, TEXT("MoveToRange Can't Find ASC"));
		return EBTNodeResult::Type::Failed;
	}

	UUPEnemyAttributeSet* TargetAttribute = const_cast<UUPEnemyAttributeSet*>(TargetASC->GetSet<UUPEnemyAttributeSet>());
	if (nullptr == TargetAttribute)
	{
		UE_LOG(LogTemp, Error, TEXT("MoveToRange Can't Find AttributeSet"));
		return EBTNodeResult::Type::Failed;
	}

	if (TargetAttribute->GetAttackRange() >= 200)
	{
		AcceptableRadiusOffset = TargetAttribute->GetAttackRange() / 3;
		AcceptableRadius = TargetAttribute->GetAttackRange() - AcceptableRadiusOffset;
	}


	EBTNodeResult::Type Result = Super::PerformMoveTask(OwnerComp, NodeMemory);
	return Result;
}