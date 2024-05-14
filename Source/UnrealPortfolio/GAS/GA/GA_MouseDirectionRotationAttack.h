// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GA_Attack.h"
#include "Abilities/GameplayAbility.h"
#include "GA_MouseDirectionRotationAttack.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPORTFOLIO_API UGA_MouseDirectionRotationAttack : public UGA_Attack
{
	GENERATED_BODY()

	virtual auto ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
							 const FGameplayAbilityActivationInfo ActivationInfo,
							 const FGameplayEventData* TriggerEventData) -> void override;
	virtual void CheckComboInput() override;
	
};
