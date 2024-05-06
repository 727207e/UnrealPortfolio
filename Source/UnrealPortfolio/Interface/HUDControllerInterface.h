// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/UPMainHudWidget.h"
#include "UObject/Interface.h"
#include "HUDControllerInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UHUDControllerInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class UNREALPORTFOLIO_API IHUDControllerInterface
{
	GENERATED_BODY()
public:
	virtual  TObjectPtr<UUPMainHudWidget> GetHudWidget() = 0;
	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
};
