// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "Data/DataAsset/UPBaseTable.h"
#include "EntityAttributeSet.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeadDelegate);

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
	ATTRIBUTE_ACCESSORS(UEntityAttributeSet, Armor);
	ATTRIBUTE_ACCESSORS(UEntityAttributeSet, AttackSpeed);
	ATTRIBUTE_ACCESSORS(UEntityAttributeSet, AttackRate);
	ATTRIBUTE_ACCESSORS(UEntityAttributeSet, MovementSpeed);
	
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual bool PreGameplayEffectExecute(struct FGameplayEffectModCallbackData& Data) override;
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;


	virtual void InitAttributeSet();
	void SetHpValue(float Value);

public:
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category = "Attack", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData Hp;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHp, Category = "Attack", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxHp;
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Attack, Category = "Attack", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData Attack;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_AttackRange, Category = "Attack", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData AttackRange;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_AttackRadius, Category = "Attack", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData AttackRadius;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Armor, Category = "Attack", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData Armor;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_AttackSpeed, Category = "Attack", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData AttackSpeed;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_AttackRate, Category = "Attack", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData AttackRate;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MovementSpeed, Category = "Attack", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MovementSpeed;
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	TObjectPtr<class UDataTable> BaseStat;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString StatName;

	virtual void GetLifetimeReplicatedProps(TArray< class FLifetimeProperty >& OutLifetimeProps) const override;

	UFUNCTION()
	virtual void OnRep_Health(const FGameplayAttributeData& OldHealth);
	UFUNCTION()
	virtual void OnRep_MaxHp(const FGameplayAttributeData& OldMaxHp);
	UFUNCTION()
	virtual void OnRep_Attack(const FGameplayAttributeData& OldAttack);
	UFUNCTION()
	virtual void OnRep_AttackRange(const FGameplayAttributeData& OldAttackRange);
	UFUNCTION()
	virtual void OnRep_AttackRadius(const FGameplayAttributeData& OldAttackRadius);
	UFUNCTION()
	virtual void OnRep_Armor(const FGameplayAttributeData& OldArmor);
	UFUNCTION()
	virtual void OnRep_AttackSpeed(const FGameplayAttributeData& OldAttackSpeed);
	UFUNCTION()
	virtual void OnRep_AttackRate(const FGameplayAttributeData& OldAttackRate);
	UFUNCTION()
	virtual void OnRep_MovementSpeed(const FGameplayAttributeData& OldMovementSpeed);

	/** Dead **/
	mutable FOnDeadDelegate OnDead;
	bool bOutOfHp = false;
	
	UAbilitySystemComponent* GetOwningASC();

protected:
	template <typename T>
	void SettingValue(T BaseTablePtr);

	template <typename T>
	T GetTableData();
};


template <typename T>
void UEntityAttributeSet::SettingValue(T BaseTablePtr)
{
	FUPBaseTable* table = static_cast<FUPBaseTable*>(&BaseTablePtr);

	SetHp(table->MaxHp);
	SetMaxHp(table->MaxHp);
	SetAttack(table->Attack);
	SetAttackRange(table->AttackRange);
	SetArmor(table->Armor);
	SetAttackSpeed(table->AttackSpeed);
	SetAttackRadius(table->AttackRadius);
	SetAttackRate(table->AttackRate);
	SetMovementSpeed(table->MovementSpeed);

	InitHp(GetMaxHp());
}

template <typename T>
T UEntityAttributeSet::GetTableData()
{
	check(BaseStat);
	TArray<FName> RowNames = BaseStat->GetRowNames();
	T table;
	for (int i = 0; i < RowNames.Num(); ++i)
	{
		if (StatName.Equals(RowNames[i].ToString()))
		{
			table = *(BaseStat->FindRow<T>(RowNames[i], RowNames[i].ToString()));
			break;
		}
	}

	return table;
}
