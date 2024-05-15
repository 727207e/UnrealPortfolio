// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/GA/Skill/GA_MainCharacterSkillHitCheck.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Data/DataAttributeSet/EntityAttributeSet.h"
#include "GAS/Actor/GameplayEventDataRequest.h"


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
	ApplyBuffEffect();
	CurrentAbilityTaskSetup();
}

void UGA_MainCharacterSkillHitCheck::ApplyBuffEffect()
{
	const FGameplayEffectSpecHandle EffectSpecHandle = MakeOutgoingGameplayEffectSpec(AttackBuffEffect,CurrentLevel);
	if (EffectSpecHandle.IsValid())
	{
		ActiveEffectHandle = ApplyGameplayEffectSpecToOwner(CurrentSpecHandle,CurrentActorInfo,CurrentActivationInfo,EffectSpecHandle);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("GA Main Skill Hit Check : Buff GA not found."));
	}
}

void UGA_MainCharacterSkillHitCheck::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	UAbilitySystemComponent* SourceASC = GetAbilitySystemComponentFromActorInfo_Checked();
	SourceASC->RemoveActiveGameplayEffect(ActiveEffectHandle);
}

void UGA_MainCharacterSkillHitCheck::ApplyDamageEffect(const UEntityAttributeSet* SourceAttribute,
	const FGameplayAbilityTargetDataHandle& TargetDataHandle)
{
	
	Super::ApplyDamageEffect(SourceAttribute, TargetDataHandle);
	UAbilitySystemComponent* SourceASC = GetAbilitySystemComponentFromActorInfo_Checked();
	SourceASC->RemoveActiveGameplayEffect(ActiveEffectHandle);
}
