// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/GE/GE_BackAttack.h"

UGE_BackAttack::UGE_BackAttack()
{
	TagTargetAttack = TAG_BACK_ATTACK_HIT;
	TagSourceAttack = TAG_BACK_ATTACK;
	TargetAngle = 125.0f;
}

void UGE_BackAttack::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
                                            FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	Super::Execute_Implementation(ExecutionParams, OutExecutionOutput);
	if(bHasAttackBonus && TargetAngle > AngleDegrees)
	{
		const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();
		const float AttackRate = Spec.GetSetByCallerMagnitude(TagDamage,false,-1.0f);
		const float DamageDone = (AttackRate * DamageBuffRatio);
		OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(DamageStatics().HpProperty,EGameplayModOp::Additive,DamageDone));
	}
}
