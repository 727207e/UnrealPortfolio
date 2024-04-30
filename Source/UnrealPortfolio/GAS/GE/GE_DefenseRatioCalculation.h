// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "Data/DataAttributeSet/EntityAttributeSet.h"
#include "GE_DefenseRatioCalculation.generated.h"

struct FDamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Armor);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Hp);
	DECLARE_ATTRIBUTE_CAPTUREDEF(AttackRate);

	FDamageStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UEntityAttributeSet,AttackRate,Source,false);
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

	static const FDamageStatics& DamageStatics();
	

};
