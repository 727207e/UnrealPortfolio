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

protected:
	int32 WEAPON_GRADE_TYPE_MAGIC = 2;
	int32 WEAPON_GRADE_TYPE_LEGEND = 3;
public:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
protected:
	UPROPERTY()
	FActiveGameplayEffectHandle LegendBuffActiveEffectHandle;
	UPROPERTY()
	FActiveGameplayEffectHandle ActiveEffectHandle;
	
	UPROPERTY(EditAnywhere, Category = "GAS")
	float AtiveSkillIndex;
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


	UPROPERTY(EditAnywhere , Category = GAS)
	TSubclassOf<class UGameplayEffect> LegendGradBuffEffect;
	void LegendWeaponProcess();

};
