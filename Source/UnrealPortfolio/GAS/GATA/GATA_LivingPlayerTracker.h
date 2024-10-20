// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTargetActor_Radius.h"
#include "Character/UPMainCharacter.h"
#include "GATA_LivingPlayerTracker.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPORTFOLIO_API AGATA_LivingPlayerTracker : public AGameplayAbilityTargetActor
{
	GENERATED_BODY()
public:
	virtual void StartTargeting(UGameplayAbility* Ability) override;
	virtual void ConfirmTargetingAndContinue() override;
};
