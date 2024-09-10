// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/GA/GA_MouseDirectionRotationAttack.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "GAS/Attribute/EntityAttributeSet.h"
#include "GAS/AbilityTask/AbilityTask_LookAtMouse.h"

class UAbilityTask_LookAtMouse;
class UEntityAttributeSet;

auto UGA_MouseDirectionRotationAttack::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                                       const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                                       const FGameplayEventData* TriggerEventData) -> void
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	UAbilityTask_LookAtMouse * AttackTraceTask = UAbilityTask_LookAtMouse::CreateTask(this);
	AttackTraceTask->ReadyForActivation();
}


void UGA_MouseDirectionRotationAttack::CheckComboInput()
{
	Super::CheckComboInput();
	UAbilityTask_LookAtMouse * AttackTraceTask = UAbilityTask_LookAtMouse::CreateTask(this);
	AttackTraceTask->ReadyForActivation();
}
