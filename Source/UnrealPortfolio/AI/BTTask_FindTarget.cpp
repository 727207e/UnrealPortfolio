// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_FindTarget.h"
#include "AIController.h"
#include "AbilitySystemComponent.h"
#include "GAS/Actor/GameplayEventDataRequest.h"
#include "GAS/GA/GA_FindTarget.h"
#include "Character/UPEnemyCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Data/DataAttributeSet/EntityAttributeSet.h"
#include "defines/UPAIDefine.h"

UBTTask_FindTarget::UBTTask_FindTarget()
{
}

EBTNodeResult::Type UBTTask_FindTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	AUPEnemyCharacter* EnemyCharacter = Cast<AUPEnemyCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == EnemyCharacter)
	{
		return EBTNodeResult::Failed;
	}

	auto FindTargetGAS = EnemyCharacter->FindTarget();
	UBlackboardComponent* BbComponent = OwnerComp.GetBlackboardComponent();
	if (FindTargetGAS.Ability == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("UBTTask_FindTarget Can't Find FindTargetGas"));
		BbComponent->SetValueAsBool(BBKEY_TARGETFIND, true);
		return EBTNodeResult::Succeeded;
	}

	UGA_FindTarget* TargetGA = Cast<UGA_FindTarget>(FindTargetGAS.Ability);
	if (nullptr == TargetGA)
	{
		UE_LOG(LogTemp, Error, TEXT("UBTTask_FindTarget Is Not GA_FindTarget"));
		BbComponent->SetValueAsBool(BBKEY_TARGETFIND, true);
		return EBTNodeResult::Succeeded;
	}

	//공격 받으면 캔슬
	FOnHitDelegate OnHitDelegate;
	OnHitDelegate.AddLambda([&, BbComponent, FindTargetGAS]() {

			//if(!EnemyCharacter->AttributeSet->bOutOfHp && FindTargetGAS.Ability)
			//{
			//	FindTargetGAS.Ability->CancelAbility(FindTargetGAS.Handle, FindTargetGAS.Ability->GetCurrentActorInfo(), FindTargetGAS.ActivationInfo, true);
			//}

			BbComponent->SetValueAsBool(BBKEY_TARGETFIND, true);
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		});
	EnemyCharacter->AddOnHitDelegate(OnHitDelegate);

	//끝나면 캔슬	
	FOnEndAnimDelegate OnEndAnim;
	OnEndAnim.BindLambda(
		[&]()
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(BBKEY_TARGETFIND, true);
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		}
	);

	EnemyCharacter->SetDelegate(OnEndAnim);
	return EBTNodeResult::InProgress;
}