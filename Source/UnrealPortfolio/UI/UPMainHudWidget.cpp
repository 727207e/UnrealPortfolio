// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UPMainHudWidget.h"
#include "Components/HorizontalBox.h"
#include "Components/WidgetComponent.h"
#include "Game/UPGameSingleton.h"

UUPMainHudWidget::UUPMainHudWidget()
{
	static ConstructorHelpers::FClassFinder<USlotViewWidget> BuffSlotRef(TEXT("/Game/UI/Hud/WBP_BuffSlot.WBP_BuffSlot_C"));
	if(BuffSlotRef.Class)
	{
		BuffViewer = BuffSlotRef.Class;
	}

}

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
	
	const int32 BuffMaxCount = UUPGameSingleton::Get().GetBuffTypeCount();
	const auto BuffSlotBox = Cast<UHorizontalBox>(GetWidgetFromName(TEXT("BuffSlotBox")));
	if(BuffSlotBox)
	{
		for(int i = 0 ; i <= BuffMaxCount; i++)
		{
			const auto NewBuffWidget = CreateWidget(GetWorld(),BuffViewer,*WIDGET_BUFF_VIEW);
			NewBuffWidget->AddToViewport();
			NewBuffWidget->SetVisibility(ESlateVisibility::Hidden);
			BuffSlotViewArray.Add(Cast<USlotViewWidget>(NewBuffWidget));
			BuffSlotBox->AddChildToHorizontalBox(NewBuffWidget);
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
		HpProgressView = Cast<UProgressViewWidget>(GetWidgetFromName(*HP_PROGRESS_WIDGET_NAME));
		if(HpProgressView)
		{
			HpProgressView->SetAbilitySystemComponent(Owner);
		}

		MpProgressView = Cast<UProgressViewWidget>(GetWidgetFromName(*MP_PROGRESS_WIDGET_NAME));
		if(MpProgressView)
		{
			MpProgressView->SetAbilitySystemComponent(Owner);
		}
	}
}

void UUPMainHudWidget::Client_BuffProcess_Implementation()
{
	FString Message = FString::Printf(TEXT("하이, %s"), *GetName());
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, Message);
	TTuple<bool, TObjectPtr<USlotViewWidget>> MyTuple =  GetLastBuffViewWidget(0);
	const bool bUsedBuff = MyTuple.Get<0>();
	const auto CurBuffSlot = MyTuple.Get<1>();
	CurBuffSlot->OnClickedTargetInputActionKey(10);
	CurBuffSlot->SetVisibility(ESlateVisibility::Visible);
	//CurBuffSlot->CooldownFinishDelegate.AddDynamic(this,&UGA_BuffTargetCheck::OnBuffEnd);
}

TTuple<bool,TObjectPtr<USlotViewWidget>> UUPMainHudWidget::GetLastBuffViewWidget(int32 CastingBuffId)
{
	bool bBuffUsed = false;
	for(const auto& BuffSlotWidget : BuffSlotViewArray)
	{
		if(BuffSlotWidget->GetVisibility() == ESlateVisibility::Hidden)
		{
			BuffSlotWidget->BuffId = CastingBuffId;
			return TTuple<bool, TObjectPtr<USlotViewWidget>>(bBuffUsed, BuffSlotWidget);
		}
	}
	UE_LOG(LogTemp,Error,TEXT("Not found unused slot"))
	bBuffUsed = true;
	for(const auto& BuffSlotWidget : BuffSlotViewArray)
	{
		if(BuffSlotWidget->BuffId != CastingBuffId)
		{
			continue;
		}
		return TTuple<bool, TObjectPtr<USlotViewWidget>>(bBuffUsed, BuffSlotWidget);
	}

	return {};
}


void UUPMainHudWidget::Server_Receive_Implementation()
{
	Client_BuffProcess();
}
