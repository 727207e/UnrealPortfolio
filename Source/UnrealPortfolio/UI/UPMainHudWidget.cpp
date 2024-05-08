// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UPMainHudWidget.h"
#include "Game/UPGameSingleton.h"
#include "View/HpProgressViewWidget.h"
#include "View/MpProgressViewWidget.h"

void UUPMainHudWidget::NativeConstruct()
{
	Super::NativeConstruct();

	for(int i = SkillSlotMinId ; i <= SkillSlotMaxId; i++)
	{
		const FName SlotSkillName = *FString::Printf(TEXT("%s%d"),TEXT("WBP_SkillSlot") ,i);
		if(auto SkillSlotView = Cast<USlotViewWidget>(GetWidgetFromName(SlotSkillName)))
		{
			SkillSlotView->SetData(UUPGameSingleton::Get().SlotWidgetModelDataArray[i]);
			SkillSlotViewArray.Add(SkillSlotView);
		}
	}

	for(int i = ItemSlotMinId ; i <= ItemSlotMaxId; i++)
	{
		const FName SlotItemName = *FString::Printf(TEXT("%s%d"),TEXT("WBP_ItemSlot") ,i);
		if(auto ItemSlotView = Cast<UItemSlotViewWidget>(GetWidgetFromName(SlotItemName)))
		{
			UE_LOG(LogTemp,Log,TEXT("Check"));
			ItemSlotView->SetData(UUPGameSingleton::Get().SlotWidgetModelDataArray[i]);
			ItemSlotViewArray.Add(ItemSlotView);
		}
		else
		{
			UE_LOG(LogTemp,Log,TEXT("Not Exsit"));
			
		}
	}

	for(int i = ProgressMinId ; i <= ProgressMaxId; i++)
	{
		const FName SlotItemName = *FString::Printf(TEXT("%s%d"),*PROGRESS_WIDGET_NAME ,i);
		if(const auto PbViewWidget = Cast<UProgressViewWidget>(GetWidgetFromName(SlotItemName)))
		{
			PbViewWidget->SetData(UUPGameSingleton::Get().ProgressWidgetModelDataArray[i]);
		}
	}
	
	
}

TArray<TObjectPtr<USlotViewWidget>> UUPMainHudWidget::GetSkillSlotArray()
{
	return SkillSlotViewArray;
}

TObjectPtr<USlotViewWidget> UUPMainHudWidget::GetSlotViewWidgetByActionId(int32 ActionId)
{
	for(const auto& SkillSlotWidget : SkillSlotViewArray)
	{
		if(SkillSlotWidget != nullptr)
		{
			if(ActionId == SkillSlotWidget->TargetInputActionId)
			{
				return SkillSlotWidget;
			}
		}
	}
	return nullptr;
}

void UUPMainHudWidget::SetProgress(AActor* Owner)
{
	if(Owner)
	{
		HpProgressView = Cast<UHpProgressViewWidget>(GetWidgetFromName(*HP_PROGRESS_WIDGET_NAME));
		if(HpProgressView)
		{
			HpProgressView->SetAbilitySystemComponent(Owner);
		}

		MpProgressView = Cast<UMpProgressViewWidget>(GetWidgetFromName(*MP_PROGRESS_WIDGET_NAME));
		if(MpProgressView)
		{
			MpProgressView->SetAbilitySystemComponent(Owner);
		}
	}
}
