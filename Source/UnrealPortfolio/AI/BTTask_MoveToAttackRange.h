// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_MoveTo.h"
#include "BTTask_MoveToAttackRange.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPORTFOLIO_API UBTTask_MoveToAttackRange : public UBTTask_MoveTo
{
	GENERATED_BODY()
	
public :
	UBTTask_MoveToAttackRange();

public:
	virtual EBTNodeResult::Type PerformMoveTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
	UPROPERTY(EditAnywhere)
	float AcceptableRadiusOffset = -1;
};