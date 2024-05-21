// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "Data/DataAttributeSet/EntityAttributeSet.h"
#include "Tag/GameplayTags.h"
#include "GE_DirectionalAttackBonus.generated.h"

USTRUCT(Blueprintable)
struct FHeadAttackDamageStatics
{
	GENERATED_BODY()
	DECLARE_ATTRIBUTE_CAPTUREDEF(Hp);

	FHeadAttackDamageStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UEntityAttributeSet, Hp, Target, false);
	}
};

UCLASS()
class UNREALPORTFOLIO_API UGE_DirectionalAttackBonus : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()
protected:
	const float DamageBuffRatio = 0.2f;
	FGameplayTag TagTargetAttack;
	FGameplayTag TagSourceAttack;
	FGameplayTag TagDamage = TAG_DATA_DAMAGE;
public:
	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
protected:
	UPROPERTY(EditAnywhere , Category =  AttackBonus)
	float TargetAngle;
	mutable float AngleDegrees;
	mutable bool bHasAttackBonus;
	static const FHeadAttackDamageStatics& DamageStatics();
};
