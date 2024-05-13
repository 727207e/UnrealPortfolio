// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "Data/DataAsset/Enemy/UPBossSkillTable.h"
#include "UPBossSkillAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */
UCLASS()
class UNREALPORTFOLIO_API UUPBossSkillAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UUPBossSkillAttributeSet();

	ATTRIBUTE_ACCESSORS(UUPBossSkillAttributeSet, Damage);
	ATTRIBUTE_ACCESSORS(UUPBossSkillAttributeSet, AttackNumber);
	ATTRIBUTE_ACCESSORS(UUPBossSkillAttributeSet, KnockBack);
	ATTRIBUTE_ACCESSORS(UUPBossSkillAttributeSet, AttackRange);
	ATTRIBUTE_ACCESSORS(UUPBossSkillAttributeSet, AttackSpeed);
	ATTRIBUTE_ACCESSORS(UUPBossSkillAttributeSet, AttackRadius);

	virtual void InitAttributeSet(int32 CurPhaseNumber);

public:
	UPROPERTY(BlueprintReadOnly, Category = "Attack", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData Damage;

	UPROPERTY(BlueprintReadOnly, Category = "Attack", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData AttackNumber;

	UPROPERTY(BlueprintReadOnly, Category = "Attack", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData KnockBack;

	UPROPERTY(BlueprintReadOnly, Category = "Attack", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData AttackRange;

	UPROPERTY(BlueprintReadOnly, Category = "Attack", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData AttackSpeed;

	UPROPERTY(BlueprintReadOnly, Category = "Attack", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData AttackRadius;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<class UDataTable> BaseStat;

protected:
	template <typename T>
	void SettingValue(T BaseTablePtr);

	template <typename T>
	T GetTableData(int32 CurPhaseNumber);
};


template <typename T>
void UUPBossSkillAttributeSet::SettingValue(T BaseTablePtr)
{
	FUPBossSkillTable* table = static_cast<FUPBossSkillTable*>(&BaseTablePtr);

	InitDamage(table->Damage);
	InitAttackNumber(table->AttackNumber);
	InitKnockBack(table->KnockBack);
	InitAttackRange(table->AttackRange);
	InitAttackSpeed(table->AttackSpeed);
	InitAttackRadius(table->AttackRadius);
}

template <typename T>
T UUPBossSkillAttributeSet::GetTableData(int32 CurPhaseNumber)
{
	check(BaseStat);
	TArray<FName> RowNames = BaseStat->GetRowNames();
	T table;
	for (int i = 0; i < RowNames.Num(); ++i)
	{
		FString SearchingString = FString(TEXT("Phase")) + FString::FromInt(CurPhaseNumber);
		if (SearchingString.Equals(RowNames[i].ToString()))
		{
			table = *(BaseStat->FindRow<T>(RowNames[i], RowNames[i].ToString()));
			break;
		}
	}

	return table;
}