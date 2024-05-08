// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/GA/Skill/GA_SkillBase.h"

#include "Character/UPMainCharacter.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"


void UGA_SkillBase::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                    const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	AttackableCharacter = CastChecked<IAttackableCharacterInterface>(ActorInfo->AvatarActor.Get());
	if(TargetMontage)
	{
		/** PlayAttackTask Ability **/
		UAbilityTask_PlayMontageAndWait* PlayAttackTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(
			this,TEXT("PlayerSkill"),TargetMontage, AttackSpeed, TargetMontageSectionName);
	
		PlayAttackTask->OnCompleted.AddDynamic(this,&UGA_SkillBase::OnCompleteCallback);
		PlayAttackTask->OnInterrupted.AddDynamic(this,&UGA_SkillBase::OnInterruptedCallback);
		PlayAttackTask->ReadyForActivation();
	}
}

void UGA_SkillBase::CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility)
{
	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);
}

void UGA_SkillBase::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	AttackableCharacter->AttackEndCallBack();
	AttackableCharacter->SkillEndCallBack();
}

void UGA_SkillBase::InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputPressed(Handle, ActorInfo, ActivationInfo);
}

void UGA_SkillBase::OnCompleteCallback()
{
	bool bReplicatedEndAbility = true;
	bool bWasCancelled = false;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicatedEndAbility, bWasCancelled);
}

void UGA_SkillBase::OnInterruptedCallback()
{
	bool bReplicatedEndAbility = true;
	bool bWasCancelled = true;
	EndAbility(CurrentSpecHandle,CurrentActorInfo,CurrentActivationInfo,bReplicatedEndAbility,bWasCancelled);
}