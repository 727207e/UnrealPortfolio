// Fill out your copyright notice in the Description page of Project Settings.
#include "GAS/GE/GE_HeadAttack.h"
#include "Character/UPBossCharacter.h"
#include "Tag/GameplayTags.h"

void UGE_HeadAttack::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	const UAbilitySystemComponent* SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();
	const UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();

	if (nullptr == SourceASC || nullptr == TargetASC)
	{
		UE_LOG(LogTemp,Error, TEXT("GU_CounterEffect Can't Find ASC"));
		return;
	}

	if (SourceASC->HasMatchingGameplayTag(TAG_HEAD_ATTACK) && TargetASC->HasMatchingGameplayTag(TAG_HEAD_ATTACK_HIT))
	{
		const FVector SourceActorFwdVector = SourceASC->GetAvatarActor()->GetActorForwardVector();
		const FVector TargetActorFwdVector = TargetASC->GetAvatarActor()->GetActorForwardVector();
		
		FVector TargetDir = TargetActorFwdVector - SourceActorFwdVector;
		TargetDir.Normalize();
		const float DotProduct = FVector::DotProduct(SourceActorFwdVector, TargetDir);
		const float Vec1Length = SourceActorFwdVector.Size();
		const float Vec2Length = TargetDir.Size();
		const float CosineAngle = DotProduct / (Vec1Length * Vec2Length);
		const float AngleRadians = FMath::Acos(CosineAngle);
		const float AngleDegrees = FMath::RadiansToDegrees(AngleRadians);
		
		if(TargetAngle < AngleDegrees)
		{
			const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();
			const float AttackRate = Spec.GetSetByCallerMagnitude(TAG_DATA_DAMAGE,false,-1.0f);
			const float DamageDone = (AttackRate * DamageBuffRatio);
			OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(DamageStatics().HpProperty,EGameplayModOp::Additive,DamageDone));
		}
	}
	
}

const FHeadAttackDamageStatics& UGE_HeadAttack::DamageStatics()
{
	static FHeadAttackDamageStatics DmgStatics;
	return DmgStatics;
}
