// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "GE_DirectionalAttackBonus.h"

#include "GE_HeadAttack.generated.h"



UCLASS()
class UNREALPORTFOLIO_API UGE_HeadAttack : public UGE_DirectionalAttackBonus
{
	GENERATED_BODY()
	
public:
	UGE_HeadAttack();
	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
	
};
