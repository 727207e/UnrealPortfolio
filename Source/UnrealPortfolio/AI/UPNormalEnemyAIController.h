// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "UPNormalEnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPORTFOLIO_API AUPNormalEnemyAIController : public AAIController
{
	GENERATED_BODY()

public :
	AUPNormalEnemyAIController();

	void RunAI();
	void StopAI();

protected :
	virtual void OnPossess(APawn* InPawn) override;

private:
	UPROPERTY()
	TObjectPtr<class UBlackboardData> BBAsset;

	UPROPERTY()
	TObjectPtr<class UBehaviorTree> BTAsset;
};
