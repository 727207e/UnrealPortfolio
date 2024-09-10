// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "GAS/Attribute/EntityAttributeSet.h"
#include "GE_DefenseRatioCalculation.generated.h"

USTRUCT(Blueprintable)
struct FDamageStatics
{
	GENERATED_BODY()
	DECLARE_ATTRIBUTE_CAPTUREDEF(Armor);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Hp);

	FDamageStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UEntityAttributeSet,Armor,Target,false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UEntityAttributeSet,Hp,Target,false);
	}
};

UCLASS()
class UNREALPORTFOLIO_API UGE_DefenseRatioCalculation : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()
public:
	UGE_DefenseRatioCalculation();
	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
private:
	const float ArmorReductionConstant = 50.0f;
	const float RoundCondition = 1000.0f;
	const float MaxRatio = 1.0f;
protected:
	static const FDamageStatics& DamageStatics();
	float CalculateDoneDamageWithArmor(float AttackRate, float Armor ) const;
	
};
