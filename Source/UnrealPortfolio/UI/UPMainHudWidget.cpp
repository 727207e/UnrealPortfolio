// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UPMainHudWidget.h"

#include "Game/UPGameSingleton.h"

void UUPMainHudWidget::NativeConstruct()
{
	Super::NativeConstruct();

	for(int i =SkillSlotMinId ; i <= SkillSlotMaxId; i++)
	{
		const FName SlotSkillName = *FString::Printf(TEXT("%s%d"),TEXT("WBP_SkillSlot") ,i);
		if(auto SkillSlotView = Cast<USlotViewWidget>(GetWidgetFromName(SlotSkillName)))
		{
			SkillSlotView->SetData(UUPGameSingleton::Get().SlotWidgetModelDataArray[i]);
			SkillSlotViewArray.Add(SkillSlotView);
		}
	}
}

TArray<TObjectPtr<USlotViewWidget>> UUPMainHudWidget::GetSkillSlotArray()
{
	return SkillSlotViewArray;
}
