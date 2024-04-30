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
	//Super::Execute_Implementation(ExecutionParams, OutExecutionOutput);
	UAbilitySystemComponent* TargetABSC = ExecutionParams.GetTargetAbilitySystemComponent();
	AActor* TargetActor = TargetABSC ? TargetABSC->GetAvatarActor() : nullptr;

	UAbilitySystemComponent* SourceABSC = ExecutionParams.GetTargetAbilitySystemComponent();
	AActor* SourceActor = SourceABSC ? SourceABSC->GetAvatarActor() : nullptr;

	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	float AttackRate = Spec.GetSetByCallerMagnitude(TAG_DATA_DAMAGE,false,-1.0f);

	float Armor = 0.0f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ArmorDef,EvaluationParameters,Armor);

	float Hp = 0.0f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().HpDef,EvaluationParameters,Hp);

	float TestDamage = 70.0f;
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(DamageStatics().HpProperty,EGameplayModOp::Additive,TestDamage));
}

const FDamageStatics& UGE_DefenseRatioCalculation::DamageStatics()
{
	static FDamageStatics DmgStatics;
	return DmgStatics;
}

