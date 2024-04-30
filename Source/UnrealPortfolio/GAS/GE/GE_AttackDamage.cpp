// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/GE/GE_AttackDamage.h"

UGE_AttackDamage::UGE_AttackDamage()
{
	DurationPolicy = EGameplayEffectDurationType::Instant;

	FGameplayModifierInfo HpModifier;
	HpModifier.Attribute = FGameplayAttribute();

	Modifiers.Add(HpModifier);
}
