// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/View/ItemSlotViewWidget.h"

#include "Game/UPGameSingleton.h"

void UItemSlotViewWidget::SetData(const FSlotWidgetModelData& Model)
{
	SetIconSlot(Model);
	ImageSlot->SetBrushResourceObject(Model.SlotTexture);
	TextKey->SetText(FText::FromString(Model.KeyString));
	TargetInputActionId = Model.InputActionId;
	HiddenCoolDown();
}
