// Fill out your copyright notice in the Description page of Project Settings.
#include "GAS/GA/Skill/GA_AvoidProcess.h"

#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Character/UPMainCharacter.h"
#include "GAS/AbilityTask/AbilityTask_LookAtMouse.h"
#include "Tag/GameplayTags.h"
#include "UI/UPMainHudWidget.h"

UGA_AvoidProcess::UGA_AvoidProcess(): UGA_MainCharacterSkillBase()
{
	ActivationOwnedTags.AddTag(TAG_PLAYER_STATE_AVOID);	
}

void UGA_AvoidProcess::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	Cast<ICharacterMovementInterface>(ActorInfo->AvatarActor)->SetMoveBlock(true);
}




void UGA_AvoidProcess::OnEndAbility()
{
	bool bReplicatedEndAbility = true;
	bool bWasCancelled = false;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicatedEndAbility, bWasCancelled);
}

void UGA_AvoidProcess::SetSlotWidget(USlotViewWidget* TargetSlotWidget)
{
	Super::SetSlotWidget(TargetSlotWidget);
	SkillSlotWidget->CooldownFinishDelegate.AddDynamic(this,&UGA_AvoidProcess::OnEndAbility);
}

void UGA_AvoidProcess::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	Cast<ICharacterMovementInterface>(ActorInfo->AvatarActor)->SetMoveBlock(false);
}
