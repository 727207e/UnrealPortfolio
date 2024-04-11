// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "UPUINpcInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UUPUINpcInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class UNREALPORTFOLIO_API IUPUINpcInterface
{
	GENERATED_BODY()

public:
	virtual  void TakeNPCWidgetShow() =0;
	virtual  void TakeNPCWidgetHide() =0;
	virtual  void ShowInteractionAlarm() =0;
	virtual  void HideInterActionAlarm() =0;
	virtual  FTransform GetNPCCameraTransform() = 0;
};
