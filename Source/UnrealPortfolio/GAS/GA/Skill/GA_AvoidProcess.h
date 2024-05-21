// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAS/GA/Skill/GA_MainCharacterSkillBase.h"
#include "UI/UPMainHudWidget.h"
#include "GA_AvoidProcess.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPORTFOLIO_API UGA_AvoidProcess : public UGA_MainCharacterSkillBase
{
	GENERATED_BODY()
	UGA_AvoidProcess();
	virtual void ActivateAbility(FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	                             FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	UFUNCTION()
	void OnEndAbility();
	virtual void SetSlotWidget(USlotViewWidget* TargetSlotWidget) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
};
