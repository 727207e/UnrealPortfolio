// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "Data/DataAsset/UPBaseTable.h"
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

	ATTRIBUTE_ACCESSORS(UEntityAttributeSet, Hp);
	ATTRIBUTE_ACCESSORS(UEntityAttributeSet, MaxHp);
	ATTRIBUTE_ACCESSORS(UEntityAttributeSet, Attack);
	ATTRIBUTE_ACCESSORS(UEntityAttributeSet, AttackRange);
	ATTRIBUTE_ACCESSORS(UEntityAttributeSet, AttackRadius);
	ATTRIBUTE_ACCESSORS(UEntityAttributeSet, AttackSize);
	ATTRIBUTE_ACCESSORS(UEntityAttributeSet, Armor);
	ATTRIBUTE_ACCESSORS(UEntityAttributeSet, AttackSpeed);
	ATTRIBUTE_ACCESSORS(UEntityAttributeSet, AttackRate);
	ATTRIBUTE_ACCESSORS(UEntityAttributeSet, MovementSpeed);
	
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual bool PreGameplayEffectExecute(struct FGameplayEffectModCallbackData& Data) override;
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;

	virtual void InitAttributeSet();

public:
	UPROPERTY(BlueprintReadOnly, Category = "Attack", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData Hp;
	
	UPROPERTY(BlueprintReadOnly, Category = "Attack", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxHp;
	
	UPROPERTY(BlueprintReadOnly, Category = "Attack", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData Attack;

	UPROPERTY(BlueprintReadOnly, Category = "Attack", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData AttackRange;

	UPROPERTY(BlueprintReadOnly, Category = "Attack", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData AttackRadius;

	UPROPERTY(BlueprintReadOnly, Category = "Attack", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData AttackSize;

	UPROPERTY(BlueprintReadOnly, Category = "Attack", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData Armor;

	UPROPERTY(BlueprintReadOnly, Category = "Attack", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData AttackSpeed;

	UPROPERTY(BlueprintReadOnly, Category = "Attack", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData AttackRate;

	UPROPERTY(BlueprintReadOnly, Category = "Attack", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MovementSpeed;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<class UDataTable> BaseStat;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString StatName;

protected:
	virtual void SettingValue(FUPBaseTable table);
	virtual FUPBaseTable GetTableData();

};