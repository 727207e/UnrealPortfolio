// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/GA/Skill/GA_BossSkill.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"

UGA_BossSkill::UGA_BossSkill()
{
	IndexNumber = 0;
}

void UGA_BossSkill::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	if (SkillSectionList.Num() > 0)
	{
		TargetMontageSectionName = SkillSectionList[IndexNumber];
		IndexNumber++;
	}

	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UGA_BossSkill::OnCompleteCallback()
{
	if (IndexNumber > SkillSectionList.Num())
	{
		TargetMontageSectionName = SkillSectionList[IndexNumber];
		IndexNumber++;

		PlayNextMontage();
	}

	else
	{
		bool bReplicatedEndAbility = true;
		bool bWasCancelled = false;
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicatedEndAbility, bWasCancelled);
	}
}

void UGA_BossSkill::PlayNextMontage()
{
	UAbilityTask_PlayMontageAndWait* PlayAttackTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(
		this, TEXT("PlayerSkill"), TargetMontage, 1.0f, TargetMontageSectionName);

	PlayAttackTask->OnCompleted.AddDynamic(this, &UGA_BossSkill::OnCompleteCallback);
	PlayAttackTask->OnInterrupted.AddDynamic(this, &UGA_BossSkill::OnInterruptedCallback);
	PlayAttackTask->ReadyForActivation();
}
