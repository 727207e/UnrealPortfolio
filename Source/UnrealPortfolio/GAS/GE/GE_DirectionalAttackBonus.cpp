// Fill out your copyright notice in the Description page of Project Settings.
#include "GAS/GE/GE_DirectionalAttackBonus.h"

void UGE_DirectionalAttackBonus::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	const UAbilitySystemComponent* SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();
	const UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();

	if (nullptr == SourceASC || nullptr == TargetASC)
	{
		UE_LOG(LogTemp,Error, TEXT("GU_DirectionalAttckBounus Can't Find ASC"));
		bHasAttackBonus =  false;
	}
	
	if (SourceASC->HasMatchingGameplayTag(TagSourceAttack) && TargetASC->HasMatchingGameplayTag(TagTargetAttack))
	{
		const FVector SourceActorFwdVector = SourceASC->GetAvatarActor()->GetActorForwardVector();
		const FVector TargetActorFwdVector = TargetASC->GetAvatarActor()->GetActorForwardVector();

		const FVector TargetDir = TargetActorFwdVector - SourceActorFwdVector;
		const float DotProduct = FVector::DotProduct(SourceActorFwdVector, TargetDir);
		const float Vec1Length = SourceActorFwdVector.Size();
		const float Vec2Length = TargetDir.Size();
		const float CosineAngle = DotProduct / (Vec1Length * Vec2Length);
		const float AngleRadians = FMath::Acos(CosineAngle);
		AngleDegrees = FMath::RadiansToDegrees(AngleRadians);
		bHasAttackBonus =  true;
	}
}

const FHeadAttackDamageStatics& UGE_DirectionalAttackBonus::DamageStatics()
{
	static FHeadAttackDamageStatics DmgStatics;
	return DmgStatics;
}

