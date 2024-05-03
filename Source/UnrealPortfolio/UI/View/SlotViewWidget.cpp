// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/View/SlotViewWidget.h"
void USlotViewWidget::NativeConstruct()
{
	Super::NativeConstruct();
	ImageSlot =  Cast<UImage>(GetWidgetFromName(TEXT("Image_Slot")));
	ImageIcon =  Cast<UImage>(GetWidgetFromName(TEXT("Image_Icon")));
	TextKey =  Cast<UTextBlock>(GetWidgetFromName(TEXT("Text_Key")));
	TextCount =  Cast<UTextBlock>(GetWidgetFromName(TEXT("Text_Count")));
}

void USlotViewWidget::SetData(const FSlotWidgetModelData& Model) const
{
	ImageSlot->SetBrushResourceObject(Model.SlotTexture);

	if(Model.IconTexture == nullptr)
	{
		TextCount->SetVisibility(ESlateVisibility::Hidden);
		ImageIcon->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		TextCount->SetText(FText::FromString(Model.CountString));
		ImageIcon->SetBrushResourceObject(Model.IconTexture);
	}
	
	TextKey->SetText(FText::FromString(Model.KeyString));
	
}

void USlotViewWidget::StartCooldown(float CooldownEndTime)
{
	
}
