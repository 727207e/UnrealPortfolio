// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "UPEnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPORTFOLIO_API AUPEnemyAIController : public AAIController
{
	GENERATED_BODY()

public :
	AUPEnemyAIController();

	void RunAI();
	void StopAI();

protected :
	virtual void OnPossess(APawn* InPawn) override;

	UPROPERTY()
	TObjectPtr<class UBlackboardData> BBAsset;

	UPROPERTY()
	TObjectPtr<class UBehaviorTree> BTAsset;
};
