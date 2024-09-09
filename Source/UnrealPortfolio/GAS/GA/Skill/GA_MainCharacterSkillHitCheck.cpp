// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/GA/Skill/GA_MainCharacterSkillHitCheck.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "GAS/Attribute/EntityAttributeSet.h"
#include "GAS/Actor/GameplayEventDataRequest.h"
#include "Interface/WeaponControlInterface.h"


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
		AtiveSkillIndex = TriggerEventData->EventMagnitude;
	}
	ApplyBuffEffect();
	CurrentAbilityTaskSetup();
}

void UGA_MainCharacterSkillHitCheck::ApplyBuffEffect()
{
	const FGameplayEffectSpecHandle EffectSpecHandle = MakeOutgoingGameplayEffectSpec(AttackBuffEffect,AtiveSkillIndex);
	if (EffectSpecHandle.IsValid())
	{
		ActiveEffectHandle = ApplyGameplayEffectSpecToOwner(CurrentSpecHandle,CurrentActorInfo,CurrentActivationInfo,EffectSpecHandle);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("GA Main Skill Hit Check : Buff GA not found."));
	}
	LegendWeaponProcess();
}

void UGA_MainCharacterSkillHitCheck::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	GetAbilitySystemComponentFromActorInfo()->RemoveActiveGameplayEffect(ActiveEffectHandle);
	GetAbilitySystemComponentFromActorInfo()->RemoveActiveGameplayEffect(LegendBuffActiveEffectHandle);
}

void UGA_MainCharacterSkillHitCheck::ApplyDamageEffect(const UEntityAttributeSet* SourceAttribute,
	const FGameplayAbilityTargetDataHandle& TargetDataHandle)
{
	Super::ApplyDamageEffect(SourceAttribute, TargetDataHandle);
	GetAbilitySystemComponentFromActorInfo()->RemoveActiveGameplayEffect(ActiveEffectHandle);
	GetAbilitySystemComponentFromActorInfo()->RemoveActiveGameplayEffect(LegendBuffActiveEffectHandle);
}

void UGA_MainCharacterSkillHitCheck::LegendWeaponProcess()
{
	if(IWeaponControlInterface* WeaponControl = Cast<IWeaponControlInterface>(GetActorInfo().AvatarActor))
	{
		if(WeaponControl->GetEquipWeapon())
		{
			const int32 Grade =  WeaponControl->GetEquipWeapon()->Grade;
			const int32 LegendSkillIndex = WeaponControl->GetEquipWeapon()->LegendSkillIndex;
			if(Grade >= WEAPON_GRADE_TYPE_LEGEND && LegendSkillIndex == AtiveSkillIndex)
			{
				UE_LOG(LogTemp,Log,TEXT("LegendSkillIndex %d"),LegendSkillIndex);
				const FGameplayEffectSpecHandle LegendEffectSpecHandle =MakeOutgoingGameplayEffectSpec(LegendGradBuffEffect,LegendSkillIndex);
				if (LegendEffectSpecHandle.IsValid())
				{
					LegendBuffActiveEffectHandle = ApplyGameplayEffectSpecToOwner(CurrentSpecHandle,CurrentActorInfo,CurrentActivationInfo,LegendEffectSpecHandle);
				}
			}
		}
	}
	
}