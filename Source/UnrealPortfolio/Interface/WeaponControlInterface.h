// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/StaticMeshWeaponComponent.h"
#include "UObject/Interface.h"
#include "WeaponControlInterface.generated.h"


// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UWeaponControlInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class UNREALPORTFOLIO_API IWeaponControlInterface
{
	GENERATED_BODY()
public:
	virtual UStaticMeshWeaponComponent* GetEquipWeapon() = 0;
};
