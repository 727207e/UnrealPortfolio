// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAS/GA/Skill/GA_SkillBase.h"
#include "GA_BossStruggleSkill.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPORTFOLIO_API UGA_BossStruggleSkill : public UGA_SkillBase
{
	GENERATED_BODY()
	
public : 
	UGA_BossStruggleSkill();

protected :
	virtual auto ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		const FGameplayEventData* TriggerEventData) -> void override;

	bool IsBossDummySettingDone();
	virtual void SettingBossDummy() {}

	float Speed = 0;

	UPROPERTY()
	TWeakObjectPtr<class ABossManager> BossManager;

	UPROPERTY()
	TWeakObjectPtr<AActor> BossDummy;
};
