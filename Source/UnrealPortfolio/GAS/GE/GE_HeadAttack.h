// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "Data/DataAttributeSet/EntityAttributeSet.h"
#include "GE_HeadAttack.generated.h"

USTRUCT(Blueprintable)
struct FHeadAttackDamageStatics
{
	GENERATED_BODY()
	DECLARE_ATTRIBUTE_CAPTUREDEF(Attack);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Hp);

	FHeadAttackDamageStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UEntityAttributeSet, Attack, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UEntityAttributeSet, Hp, Target, false);
	}
};


UCLASS()
class UNREALPORTFOLIO_API UGE_HeadAttack : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()
private:
	const float DamageBuffRatio = 0.2f;
	const float TargetAngle = 145.0f;
public:
	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
protected:
	static const FHeadAttackDamageStatics& DamageStatics();

	
};
