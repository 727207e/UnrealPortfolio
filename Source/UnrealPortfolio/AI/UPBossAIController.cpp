// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/UPBossAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "defines/UPAIDefine.h"

AUPBossAIController::AUPBossAIController()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBAssetRef(TEXT("/Script/AIModule.BlackboardData'/Game/Blueprint/Animation/Enemy/AI/BB_Boss.BB_Boss'"));
	if (nullptr != BBAssetRef.Object)
	{
		BBAsset = BBAssetRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTAssetRef(TEXT("/Script/AIModule.BehaviorTree'/Game/Blueprint/Animation/Enemy/AI/BT_Boss.BT_Boss'"));
	if (nullptr != BTAssetRef.Object)
	{
		BTAsset = BTAssetRef.Object;
	}
}

void AUPBossAIController::SetBossCanMove(bool bIsCanMove)
{
	GetBlackboardComponent()->SetValueAsBool(BBKEY_CANMOVE, bIsCanMove);
}

void AUPBossAIController::RunAI()
{
	Super::RunAI();

	SetBossCanMove(true);
	FTimerHandle SetMoveTimer;
	GetWorld()->GetTimerManager().SetTimer(SetMoveTimer, FTimerDelegate::CreateLambda([&]
		{
		}), 2.0f, false);
}
