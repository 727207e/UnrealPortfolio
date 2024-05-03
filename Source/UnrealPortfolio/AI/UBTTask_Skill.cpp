// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/UBTTask_Skill.h"
#include "defines/UPAIDefine.h"
#include "AIController.h"
#include "Character/UPBattleBaseCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

UUBTTask_Skill::UUBTTask_Skill()
{
}

EBTNodeResult::Type UUBTTask_Skill::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* TargetBlackBoard = OwnerComp.GetBlackboardComponent();
	int32 CurrentSkillNumber = TargetBlackBoard->GetValueAsInt(BBKEY_SKILLNUMBER);

	AUPBattleBaseCharacter* TargetBattleCharacter =	Cast<AUPBattleBaseCharacter>(OwnerComp.GetAIOwner()->GetPawn());

	FOnEndAttackDelegate OnAttackFinished;
	OnAttackFinished.AddLambda(
		[&]()
		{
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		}
	);

	TargetBattleCharacter->OnSkill(CurrentSkillNumber);
	TargetBattleCharacter->AddAttackEndCallBack(OnAttackFinished);
	return EBTNodeResult::InProgress;
}
