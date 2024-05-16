// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAS/GA/GA_SkillCheck.h"
#include "GA_SkillCheckWithoutAttribute.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPORTFOLIO_API UGA_SkillCheckWithoutAttribute : public UGA_SkillCheck
{
	GENERATED_BODY()
	
public :
	UGA_SkillCheckWithoutAttribute();

protected :
	virtual void AttackSequence(const FGameplayAbilityTargetDataHandle& TargetDataHandle, FVector TargetLocation, AActor* TargetActor) override;
};
