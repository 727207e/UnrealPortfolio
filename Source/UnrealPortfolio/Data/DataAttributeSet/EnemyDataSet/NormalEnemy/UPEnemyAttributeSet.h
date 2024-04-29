// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/DataAttributeSet/EntityAttributeSet.h"
#include "AbilitySystemComponent.h"
#include "UPEnemyAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPORTFOLIO_API UUPEnemyAttributeSet : public UEntityAttributeSet
{
	GENERATED_BODY()
	
public:
	UUPEnemyAttributeSet();
	
	ATTRIBUTE_ACCESSORS(UUPEnemyAttributeSet, FleezeTime);
	ATTRIBUTE_ACCESSORS(UUPEnemyAttributeSet, TargetSearchingRange);

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual bool PreGameplayEffectExecute(struct FGameplayEffectModCallbackData& Data) override;
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;

protected:

	UPROPERTY(BlueprintReadOnly, Category = "Attack", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MyAttackKnockback;
	
	UPROPERTY(BlueprintReadOnly, Category = "Attack", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData FleezeTime;

	UPROPERTY(BlueprintReadOnly, Category = "Attack", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData TargetSearchingRange;

protected:
	virtual void SettingValue(FUPBaseTable table) override;
};