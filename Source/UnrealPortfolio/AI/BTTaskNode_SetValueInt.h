// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskNode_SetValueInt.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPORTFOLIO_API UBTTaskNode_SetValueInt : public UBTTaskNode
{
	GENERATED_BODY()
	
public :
	UBTTaskNode_SetValueInt();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere)
	FName TargetValue;

	UPROPERTY(EditAnywhere)
	int32 TargetInt;
};
