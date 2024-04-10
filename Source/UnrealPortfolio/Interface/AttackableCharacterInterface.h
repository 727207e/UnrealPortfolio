// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
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
	virtual class UAnimMontage* GetComboActionMontage() const = 0;
	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
};
