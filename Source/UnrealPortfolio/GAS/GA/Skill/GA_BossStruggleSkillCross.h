// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAS/GA/Skill/GA_SkillBase.h"
#include "GA_BossStruggleSkillCross.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPORTFOLIO_API UGA_BossStruggleSkillCross : public UGA_SkillBase
{
	GENERATED_BODY()
	
public : 
	UGA_BossStruggleSkillCross();

protected :
	virtual auto ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		const FGameplayEventData* TriggerEventData) -> void override;

	float Speed = 0;

private :
	UFUNCTION()
	void BossFlyForward();

	TWeakObjectPtr<AActor> BossDummy;
};
