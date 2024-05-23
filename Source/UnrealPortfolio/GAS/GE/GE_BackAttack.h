// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAS/GE/GE_DirectionalAttackBonus.h"
#include "GE_BackAttack.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPORTFOLIO_API UGE_BackAttack : public UGE_DirectionalAttackBonus
{
	GENERATED_BODY()
	UGE_BackAttack();
public:
	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
	
};
