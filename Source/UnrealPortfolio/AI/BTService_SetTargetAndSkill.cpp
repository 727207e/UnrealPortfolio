// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTService_SetTargetAndSkill.h"
#include "Player/UPPlayerController.h"
#include "AIController.h"
#include "Tag/GameplayTags.h"
#include "Abilities/GameplayAbility.h"
#include "GameplayTagContainer.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "defines/UPAIDefine.h"

UBTService_SetTargetAndSkill::UBTService_SetTargetAndSkill()
{
	NodeName = TEXT("SetTargetAndSkill");
	Interval = 1.0f;
	bGameStartFirst = true;
}

void UBTService_SetTargetAndSkill::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	UBlackboardComponent* TargetBlackBoard = OwnerComp.GetBlackboardComponent();
	int32 CurTimer = TargetBlackBoard->GetValueAsInt(BBKEY_CHANGETIMER);
	if (CurTimer < NewSearchLimitTime)
	{
		TargetBlackBoard->SetValueAsInt(BBKEY_CHANGETIMER, ++CurTimer);
		return;
	}

	TargetBlackBoard->SetValueAsInt(BBKEY_CHANGETIMER, 0);
	TargetBlackBoard->SetValueAsObject(BBKEY_TARGET, ChangeTarget());
	TargetBlackBoard->SetValueAsInt(BBKEY_SKILLNUMBER, ChangeSkillNumber(OwnerComp));
}

void UBTService_SetTargetAndSkill::OnSearchStart(FBehaviorTreeSearchData& SearchData)
{
	Super::OnSearchStart(SearchData);

	if (bGameStartFirst)
	{
		SearchData.OwnerComp.GetBlackboardComponent()->SetValueAsInt(BBKEY_CHANGETIMER, 99);
		bGameStartFirst = false;
	}
}

APawn* UBTService_SetTargetAndSkill::ChangeTarget()
{
	int32 PlayerNumber = GetWorld()->GetNumPlayerControllers();
	int32 RandomIndex = std::rand() % PlayerNumber;

	for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It) {
		APlayerController* PlayerController = It->Get();

		if (It.GetIndex() == RandomIndex) {
			return PlayerController->GetPawn();
		}
	}

	return nullptr;
}

int32 UBTService_SetTargetAndSkill::ChangeSkillNumber(UBehaviorTreeComponent& OwnerComp)
{
	int32 Result = 0;

	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == TargetASC)
	{
		UE_LOG(LogTemp, Error, TEXT("BTService_SetTargetAndSkill Can't Find ASC"));
		return Result;
	}

	TArray<FGameplayAbilitySpec> ActivatedAbilities = TargetASC->GetActivatableAbilities();

	for (FGameplayAbilitySpec AbilitySpec : ActivatedAbilities) 
	{
		if (AbilitySpec.Ability && AbilitySpec.Ability->AbilityTags.HasTag(TAG_BOSS_ATTACK))
		{
			Result++;
		}
	}
	Result = std::rand() % Result;

	return Result;
}
