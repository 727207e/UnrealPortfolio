// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "AttackReplaceDataInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UAttackReplaceDataInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class UNREALPORTFOLIO_API IAttackReplaceDataInterface
{
	GENERATED_BODY()

public:
	virtual float GetAttackValue() = 0;
};
