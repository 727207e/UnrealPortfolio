// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_SetTargetAndSkill.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPORTFOLIO_API UBTService_SetTargetAndSkill : public UBTService
{
	GENERATED_BODY()
	
public :
	UBTService_SetTargetAndSkill();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private :
	const float NewSearchLimitTime = 5.0f;
	APawn* ChangeTarget();
	int32 ChangeSkillNumber(class UBehaviorTreeComponent& OwnerComp);
};
