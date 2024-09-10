// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "GAS/Attribute/EntityAttributeSet.h"
#include "UPBossAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPORTFOLIO_API UUPBossAttributeSet : public UEntityAttributeSet
{
	GENERATED_BODY()
	
public:
	UUPBossAttributeSet();

	ATTRIBUTE_ACCESSORS(UUPBossAttributeSet, FleezeTime);

	virtual void InitAttributeSet() override;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Attack", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData FleezeTime;

};
