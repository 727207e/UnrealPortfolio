// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTaskNode_SetValueInt.h"
#include "BehaviorTree/BlackboardComponent.h"


UBTTaskNode_SetValueInt::UBTTaskNode_SetValueInt()
{
}

EBTNodeResult::Type UBTTaskNode_SetValueInt::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	OwnerComp.GetBlackboardComponent()->SetValueAsInt(TargetValue, TargetInt);

	return EBTNodeResult::Succeeded;
}

