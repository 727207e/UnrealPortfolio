// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GameplayTagContainer.h"
#include "Data/UPComboActionData.h"
#include "AttackableCharacterInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UAttackableCharacterInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class UNREALPORTFOLIO_API IAttackableCharacterInterface
{
	GENERATED_BODY()
public:
	virtual UAnimMontage* GetComboActionMontage() = 0;
	virtual UUPComboActionData* GetComboActionData() const = 0;
	virtual void Hit(FVector_NetQuantizeNormal data) = 0;
public:
};
