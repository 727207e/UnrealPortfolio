// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CharacterMovementInterface.generated.h"

UENUM(BlueprintType)
enum class ECharacterControlType : uint8
{
	TopDown,
	Shoulder,
	SideScroll,
};

UINTERFACE(MinimalAPI)
class UCharacterMovementInterface : public UInterface
{
	GENERATED_BODY()
};

class UNREALPORTFOLIO_API ICharacterMovementInterface
{
	GENERATED_BODY()

public:
	virtual void SetCharacterMovementMod(EMovementMode MovementMode) = 0;
	virtual ECharacterControlType GetCharacterControl() = 0;
	virtual void SetCharacterControl(ECharacterControlType NewCharacterControlType) = 0;
};
