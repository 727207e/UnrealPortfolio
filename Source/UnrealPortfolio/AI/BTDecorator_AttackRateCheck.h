// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_AttackRateCheck.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPORTFOLIO_API UBTDecorator_AttackRateCheck : public UBTDecorator
{
	GENERATED_BODY()
	
public:
	UBTDecorator_AttackRateCheck();
protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
