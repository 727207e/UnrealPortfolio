// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GAS/GA/GA_AttackHitCheck.h"
#include "Data/DataAttributeSet/EntityAttributeSet.h"
#include "GA_MainCharacterSkillHitCheck.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPORTFOLIO_API UGA_MainCharacterSkillHitCheck : public UGA_AttackHitCheck
{
	GENERATED_BODY()
	UPROPERTY()
	FActiveGameplayEffectHandle ActiveEffectHandle;
public:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
protected:
	UPROPERTY(EditAnywhere, Category = "GAS")
	float CurrentLevel;
	UPROPERTY(EditAnywhere, Category = "GAS")
	TSubclassOf<class UGameplayEffect> AttackBuffEffect;
	UFUNCTION()
	virtual void ApplyBuffEffect();
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle,
						const FGameplayAbilityActorInfo* ActorInfo,
						const FGameplayAbilityActivationInfo ActivationInfo,
						bool bReplicateEndAbility,
						bool bWasCancelled) override;
	
	virtual void ApplyDamageEffect(const UEntityAttributeSet* SourceAttribute, const FGameplayAbilityTargetDataHandle& TargetDataHandle) override;
	
};
