// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_Attack.h"
#include "GAS/GA/GA_Attack.h"
#include "Character/UPBattleBaseCharacter.h"
#include "AIController.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Data/DataAttributeSet/EnemyDataSet/NormalEnemy/UPEnemyAttributeSet.h"

UBTTask_Attack::UBTTask_Attack()
{
}

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	APawn* ControllingPawn = Cast<APawn>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == ControllingPawn)
	{
		return EBTNodeResult::Failed;
	}

	AUPBattleBaseCharacter* BattleCharacter = Cast<AUPBattleBaseCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == BattleCharacter)
	{
		return EBTNodeResult::Failed;
	}

	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(ControllingPawn);
	if (nullptr == TargetASC)
	{
		UE_LOG(LogTemp, Error, TEXT("Enemy Can't Find ASC"));
		return EBTNodeResult::Failed;
	}

	UUPEnemyAttributeSet* TargetAttribute = const_cast<UUPEnemyAttributeSet*>(TargetASC->GetSet<UUPEnemyAttributeSet>());
	if (nullptr == TargetAttribute)
	{
		UE_LOG(LogTemp, Error, TEXT("Enemy Can't Find AttributeSet"));
		return EBTNodeResult::Failed;
	}

	FOnEndAttackDelegate OnAttackFinished;
	OnAttackFinished.AddLambda(
		[&]()
		{
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		}
	);

	BattleCharacter->NormalAttack();
	BattleCharacter->AddAttackEndCallBack(OnAttackFinished);
	return EBTNodeResult::InProgress;
}