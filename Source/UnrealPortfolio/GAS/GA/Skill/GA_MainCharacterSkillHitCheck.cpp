// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/GA/Skill/GA_MainCharacterSkillHitCheck.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Data/DataAttributeSet/EntityAttributeSet.h"
#include "GAS/Actor/GameplayEventDataRequest.h"
#include "Interface/AttackableCharacterInterface.h"
#include "Tag/GameplayTags.h"


class UAbilityTask_Trace;

void UGA_MainCharacterSkillHitCheck::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                                     const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                                     const FGameplayEventData* TriggerEventData)
{
	CurrentAction = Cast<AGameplayEventDataRequest>(TriggerEventData->Instigator);
	if (TriggerEventData->OptionalObject)
	{
		CurrentTA = Cast<UClass>(TriggerEventData->OptionalObject);
	}
	if(TriggerEventData != nullptr)
	{
		CurrentLevel = TriggerEventData->EventMagnitude;
	}
	OnPrevTraceResultCallback();
	CurrentAbilityTaskSetup();
}

void UGA_MainCharacterSkillHitCheck::OnPrevTraceResultCallback()
{
	const FGameplayEffectSpecHandle EffectSpecHandle = MakeOutgoingGameplayEffectSpec(AttackBuffEffect,CurrentLevel);
	if (EffectSpecHandle.IsValid())
	{
		const FActiveGameplayEffectHandle ActiveGeHandle = ApplyGameplayEffectSpecToOwner(CurrentSpecHandle,CurrentActorInfo,CurrentActivationInfo,EffectSpecHandle);
	}
}
