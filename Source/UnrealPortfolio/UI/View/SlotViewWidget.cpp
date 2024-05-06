// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/View/SlotViewWidget.h"

#include "Kismet/KismetSystemLibrary.h"

void USlotViewWidget::NativeConstruct()
{
	Super::NativeConstruct();
	ImageSlot =  Cast<UImage>(GetWidgetFromName(TEXT("Image_Slot")));
	ImageIcon =  Cast<UImage>(GetWidgetFromName(TEXT("Image_Icon")));
	TextKey =  Cast<UTextBlock>(GetWidgetFromName(TEXT("Text_Key")));
	TextCount =  Cast<UTextBlock>(GetWidgetFromName(TEXT("Text_Count")));
	
	/** CoolDown **/
	ImageCoolDownDimmed = Cast<UImage>(GetWidgetFromName(TEXT("Image_CoolDown")));
	ImageCoolDownFill = Cast<UImage>(GetWidgetFromName(TEXT("Image_CoolDown")));
	TextCoolDown = Cast<UTextBlock>(GetWidgetFromName(TEXT("Text_CoolDown")));
}

void USlotViewWidget::SetData(const FSlotWidgetModelData& Model)
{
	SetIconSlot(Model);
	ImageSlot->SetBrushResourceObject(Model.SlotTexture);
	TextKey->SetText(FText::FromString(Model.KeyString));
	TargetInputActionId = Model.InputActionId;
	HiddenCoolDown();
}

void USlotViewWidget::StartCooldown(float Cooldown)
{
	DelTime = 0.0f;
	MaxCooldown = Cooldown;
	CollDownVariableFill = 1.0f;
	TextCoolDown->SetText(	FText::AsNumber(MaxCooldown));
	ShowCollDown();
	GetWorld()->GetTimerManager().SetTimer(CooldownTimer,this,&USlotViewWidget::CooldownEvent,1,true,1);
}

void USlotViewWidget::HiddenCoolDown()
{
	ImageCoolDownDimmed->SetVisibility(ESlateVisibility::Hidden);
	ImageCoolDownFill->SetVisibility(ESlateVisibility::Hidden);
	TextCoolDown->SetVisibility(ESlateVisibility::Hidden);
}

void USlotViewWidget::ShowCollDown()
{
	ImageCoolDownDimmed->SetVisibility(ESlateVisibility::Visible);
	ImageCoolDownFill->SetVisibility(ESlateVisibility::Visible);
	TextCoolDown->SetVisibility(ESlateVisibility::Visible);
}

void USlotViewWidget::SetIconSlot(const FSlotWidgetModelData& Model)
{
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
}

void USlotViewWidget::CooldownEvent()
{
	if(!CooldownTimer.IsValid())
	{
		return;
	}
	
	DelTime += UKismetSystemLibrary::K2_GetTimerElapsedTimeHandle(GetWorld(),CooldownTimer);
	CurrentCooldown = MaxCooldown - DelTime;
	CollDownVariableFill = FMath::Lerp(0.0f,1.0f,CurrentCooldown);
	const int32 CoolDownCount = FMath::RoundToInt(CurrentCooldown);
	TextCoolDown->SetText(	FText::AsNumber(CoolDownCount));
	if(CurrentCooldown <= 0)
	{
		GetWorld()->GetTimerManager().ClearTimer(CooldownTimer);
		HiddenCoolDown();
	}
}

void USlotViewWidget::OnClickedTargetInputActionKey(int32 Cooldown)
{
	StartCooldown(Cooldown);
}




