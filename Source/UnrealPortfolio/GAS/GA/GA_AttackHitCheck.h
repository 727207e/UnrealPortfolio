// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Data/DataAttributeSet/EntityAttributeSet.h"
#include "GA_AttackHitCheck.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPORTFOLIO_API UGA_AttackHitCheck : public UGameplayAbility
{
	GENERATED_BODY()
public:
	UGA_AttackHitCheck();
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
protected:
	UFUNCTION()
	virtual  void OnTraceResultCallback(const FGameplayAbilityTargetDataHandle& TargetDataHandle);
	UPROPERTY(EditAnywhere, Category = "GAS")
	TSubclassOf<class UGameplayEffect> AttackDamageEffect;
	UClass* CurrentTA;
	UPROPERTY(EditAnywhere, Category = "GAS")
	TObjectPtr<class AGameplayEventDataRequest> CurrentAction;
	
	virtual void CurrentAbilityTaskSetup();
	virtual void ApplyDamageEffect(const UEntityAttributeSet* SourceAttribute ,const FGameplayAbilityTargetDataHandle& TargetDataHandle);
};
