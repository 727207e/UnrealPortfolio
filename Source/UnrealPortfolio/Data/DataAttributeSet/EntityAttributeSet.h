// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "EntityAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */
UCLASS()
class UNREALPORTFOLIO_API UEntityAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	UEntityAttributeSet();

	ATTRIBUTE_ACCESSORS(UEntityAttributeSet, AttackRate);
	ATTRIBUTE_ACCESSORS(UEntityAttributeSet, MaxAttackRate);
	ATTRIBUTE_ACCESSORS(UEntityAttributeSet, Health);
	ATTRIBUTE_ACCESSORS(UEntityAttributeSet, MaxHealth);
	ATTRIBUTE_ACCESSORS(UEntityAttributeSet, Damage);
	ATTRIBUTE_ACCESSORS(UEntityAttributeSet, Defense);
	ATTRIBUTE_ACCESSORS(UEntityAttributeSet, MaxDefense);

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual bool PreGameplayEffectExecute(struct FGameplayEffectModCallbackData& Data) override;
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Attack", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData AttackRate;

	UPROPERTY(BlueprintReadOnly, Category = "Attack", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxAttackRate;

	UPROPERTY(BlueprintReadOnly, Category = "Health", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData Health;

	UPROPERTY(BlueprintReadOnly, Category = "Health", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxHealth;
	
	UPROPERTY(BlueprintReadOnly, Category = "Damage", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData Damage;

	UPROPERTY(BlueprintReadOnly, Category = "Defense", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData Defense;
	
	UPROPERTY(BlueprintReadOnly, Category = "Defense", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxDefense;
};
