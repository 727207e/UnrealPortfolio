// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/GA/GA_FindTarget.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Character/UPEnemyCharacter.h"

void UGA_FindTarget::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	/** Attackable Setup **/
	TargetEnemy = Cast<AUPEnemyCharacter>(ActorInfo->AvatarActor.Get());
	if (nullptr == TargetEnemy)
	{
		UE_LOG(LogTemp, Error, TEXT("GA_FindTarget Can't TargetEnemy"));
		return;
	}

	/** PlayAttackTask Ability **/
	UAbilityTask_PlayMontageAndWait* PlayAttackTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(
		this, TEXT("FindTarget"),
		TargetEnemy->FindTargetMontage, 1.0f);

	PlayAttackTask->OnCompleted.AddDynamic(this, &UGA_FindTarget::OnCompleteCallback);
	PlayAttackTask->OnInterrupted.AddDynamic(this, &UGA_FindTarget::OnInterruptedCallback);
	PlayAttackTask->ReadyForActivation();
}

void UGA_FindTarget::CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility)
{
	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);
}

void UGA_FindTarget::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	TargetEnemy->OnFindTargetEnd();
}

void UGA_FindTarget::OnCompleteCallback()
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}

void UGA_FindTarget::OnInterruptedCallback()
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
}
