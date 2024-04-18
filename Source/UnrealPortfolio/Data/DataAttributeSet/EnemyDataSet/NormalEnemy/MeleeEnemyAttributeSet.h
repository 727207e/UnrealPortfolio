// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/DataAttributeSet/EntityAttributeSet.h"
#include "MeleeEnemyAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPORTFOLIO_API UMeleeEnemyAttributeSet : public UEntityAttributeSet
{
	GENERATED_BODY()

public:
	UMeleeEnemyAttributeSet();

	ATTRIBUTE_ACCESSORS(UMeleeEnemyAttributeSet, MyAttackKnockback);
	ATTRIBUTE_ACCESSORS(UMeleeEnemyAttributeSet, MyBodyFreezeTime);
	ATTRIBUTE_ACCESSORS(UMeleeEnemyAttributeSet, TargetSearchRange);
	ATTRIBUTE_ACCESSORS(UMeleeEnemyAttributeSet, AttackRadius);
	ATTRIBUTE_ACCESSORS(UMeleeEnemyAttributeSet, AttackRange);
	ATTRIBUTE_ACCESSORS(UMeleeEnemyAttributeSet, AttackSpeed);

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual bool PreGameplayEffectExecute(struct FGameplayEffectModCallbackData& Data) override;
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Knockback", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MyAttackKnockback;

	UPROPERTY(BlueprintReadOnly, Category = "Freeze", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MyBodyFreezeTime;

	UPROPERTY(BlueprintReadOnly, Category = "Search", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData TargetSearchRange;

	UPROPERTY(BlueprintReadOnly, Category = "Attack", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData AttackRadius;
	
	UPROPERTY(BlueprintReadOnly, Category = "Attack", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData AttackRange;

	UPROPERTY(BlueprintReadOnly, Category = "Attack", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData AttackSpeed;
};
