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
	virtual auto ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
							 const FGameplayAbilityActivationInfo ActivationInfo,
							 const FGameplayEventData* TriggerEventData) -> void override;
	UGA_AvoidProcess();
	UFUNCTION()
	void OnEndAbility();
	virtual void SetSlotWidget(USlotViewWidget* TargetSlotWidget) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	virtual void MontageAbility() override;
	virtual void OnCompleteCallback() override;
};
