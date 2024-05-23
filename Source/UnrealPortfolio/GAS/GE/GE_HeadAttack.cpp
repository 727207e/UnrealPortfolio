// Fill out your copyright notice in the Description page of Project Settings.
#include "GAS/GE/GE_HeadAttack.h"

UGE_HeadAttack::UGE_HeadAttack()
{
	TagTargetAttack = TAG_HEAD_ATTACK_HIT;
	TagSourceAttack = TAG_HEAD_ATTACK;
	TargetAngle = 125.0f;
}

void UGE_HeadAttack::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
                                            FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	Super::Execute_Implementation(ExecutionParams, OutExecutionOutput);
	
	if(bHasAttackBonus && TargetAngle < AngleDegrees)
	{
		const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();
		const float AttackRate = Spec.GetSetByCallerMagnitude(TagDamage,false,-1.0f);
		const float DamageDone = (AttackRate * DamageBuffRatio);
		OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(DamageStatics().HpProperty,EGameplayModOp::Additive,DamageDone));
		UE_LOG(LogTemp,Log,TEXT("백어택 성공 TargetAngle %f AngleDegrees %f 추가피해 %f"),TargetAngle,AngleDegrees,DamageDone);
	}
}
