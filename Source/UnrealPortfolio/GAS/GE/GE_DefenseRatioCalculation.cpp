// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/GE/GE_DefenseRatioCalculation.h"

#include "Data/DataAttributeSet/EntityAttributeSet.h"
#include "Tag/GameplayTags.h"



UGE_DefenseRatioCalculation::UGE_DefenseRatioCalculation()
{
	RelevantAttributesToCapture.Add(DamageStatics().ArmorDef);
	RelevantAttributesToCapture.Add(DamageStatics().HpDef);
}

void UGE_DefenseRatioCalculation::Execute_Implementation(
	const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	//추후 사용을 위해 잠시 주석
	//Super::Execute_Implementation(ExecutionParams, OutExecutionOutput);
	// UAbilitySystemComponent* TargetABSC = ExecutionParams.GetTargetAbilitySystemComponent();
	// AActor* TargetActor = TargetABSC ? TargetABSC->GetAvatarActor() : nullptr;
	//
	// UAbilitySystemComponent* SourceABSC = ExecutionParams.GetTargetAbilitySystemComponent();
	// AActor* SourceActor = SourceABSC ? SourceABSC->GetAvatarActor() : nullptr;

	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	const float AttackRate = Spec.GetSetByCallerMagnitude(TAG_DATA_DAMAGE,false,-1.0f);
	float Armor = 0.0f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ArmorDef,EvaluationParameters,Armor);
	const float DamageDone = CalculateDoneDamageWithArmor(AttackRate,Armor);
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(DamageStatics().HpProperty,EGameplayModOp::Additive,DamageDone));
}

const FDamageStatics& UGE_DefenseRatioCalculation::DamageStatics()
{
	static FDamageStatics DmgStatics;
	return DmgStatics;
}

float UGE_DefenseRatioCalculation::CalculateDoneDamageWithArmor(float AttackRate, float Armor) const
{
	const float ArmorRatio = (Armor / (Armor + ArmorReductionConstant));
	const float ArmorRatioRound = FMath::RoundToFloat(ArmorRatio * RoundCondition) / RoundCondition;
	const float DamageDone = (AttackRate * (MaxRatio - ArmorRatioRound));
	return  DamageDone;
}