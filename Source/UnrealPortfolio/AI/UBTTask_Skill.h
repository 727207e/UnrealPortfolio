// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "UBTTask_Skill.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPORTFOLIO_API UUBTTask_Skill : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UUBTTask_Skill();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};