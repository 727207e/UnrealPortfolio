// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/GE/GE_AttackDamage.h"

UGE_AttackDamage::UGE_AttackDamage()
{
	DurationPolicy = EGameplayEffectDurationType::Instant;

	FGameplayModifierInfo HpModifier;
	HpModifier.Attribute = FGameplayAttribute();

	Modifiers.Add(HpModifier);
}

float UGE_AttackDamage::CalculateArmorRatio(float BaseDamage, float AttributeArmor)
{
	float ArmorRatio =  (AttributeArmor / (AttributeArmor + 50.0f));
	ArmorRatio = FMath::RoundToFloat(ArmorRatio * 1000.0f) / 1000.0f;
	const float AdjustedDamage = BaseDamage * (1.0f - ArmorRatio);
	return AdjustedDamage;
}
