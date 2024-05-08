// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/View/SlotViewWidget.h"
#include "ItemSlotViewWidget.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPORTFOLIO_API UItemSlotViewWidget : public USlotViewWidget
{
	GENERATED_BODY()
public:
	virtual void SetData(const FSlotWidgetModelData& Model) override;
};
