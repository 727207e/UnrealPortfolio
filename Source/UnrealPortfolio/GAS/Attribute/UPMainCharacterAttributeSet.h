// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/DataAsset/MainCharacter/UPMainCharacterClassTable.h"
#include "Data/DataAttributeSet/EntityAttributeSet.h"
#include "UPMainCharacterAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */
UCLASS()
class UNREALPORTFOLIO_API UUPMainCharacterAttributeSet : public UEntityAttributeSet
{
	GENERATED_BODY()

public:
	UUPMainCharacterAttributeSet();

	ATTRIBUTE_ACCESSORS(UUPMainCharacterAttributeSet, Mp);
	ATTRIBUTE_ACCESSORS(UUPMainCharacterAttributeSet, MaxMp);

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void GetLifetimeReplicatedProps(TArray< class FLifetimeProperty >& OutLifetimeProps) const override;
	UFUNCTION()
	virtual void OnRep_MaxMp(const FGameplayAttributeData& OldMaxMp);
	UFUNCTION()
	virtual void OnRep_Mp(const FGameplayAttributeData& OldMp);
	
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_Mp, Category = "MP", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData Mp;
	
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_MaxMp, Category = "MP", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxMp;
	
	void MainCharacterSettingValue(const FUPMainCharacterClassTable& Table);
	
	virtual  void InitAttributeSet() override;
};
