// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "UPPossessCharacterInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UUPPossessCharacterInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class UNREALPORTFOLIO_API IUPPossessCharacterInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual	void OnAttackStart() = 0;
	virtual void OnSkillStart(int32 Index) = 0;
	virtual void OnSkillRelease(int32 Index) = 0;
	virtual void OnConsumableStart(int32 Index) = 0;
	virtual void OnAvoidStart() = 0;
	virtual void OnMenuStart() = 0;
	virtual void OnInventoryStart() = 0;

	virtual void OnInputStart() = 0;
	virtual void OnSetDestinationTriggered() = 0;
	virtual void OnSetDestinationReleased() = 0;
	virtual void OnNPCInteraction(int32 InputId) = 0;
};