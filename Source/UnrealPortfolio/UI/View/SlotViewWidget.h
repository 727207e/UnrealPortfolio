// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Data/DataTable/Widget/SlotWidgetModelData.h"
#include "UI/UPUserWidget.h"
#include "SlotViewWidget.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPORTFOLIO_API USlotViewWidget : public UUPUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

protected:
	UPROPERTY(EditAnywhere, Category = Slot)
	TObjectPtr<class UImage> ImageSlot;

	UPROPERTY(EditAnywhere, Category = Slot)
	TObjectPtr<class UImage> ImageIcon;

	UPROPERTY(EditAnywhere, Category = Slot)
	TObjectPtr<class UTextBlock> TextKey;
	
	UPROPERTY(EditAnywhere, Category = Slot)
	TObjectPtr<class UTextBlock> TextCount;

public:
	virtual void SetData(const FSlotWidgetModelData& Model) const;
	virtual void StartCooldown(float CooldownEndTime);
	
};
