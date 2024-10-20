// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GA_ConsumableCheck.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPORTFOLIO_API UGA_ConsumableCheck : public UGameplayAbility
{
	GENERATED_BODY()
	
protected :

	UPROPERTY(EditAnywhere, Category = "GAS")
	TSubclassOf<class UGameplayEffect> ConsumableGE;

	int32 ConsumableGEValue;

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
		bool bReplicateEndAbility,
		bool bWasCancelled) override;
};

