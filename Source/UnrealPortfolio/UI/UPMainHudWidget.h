// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/UPUserWidget.h"
#include "View/ItemSlotViewWidget.h"
#include "View/ProgressViewWidget.h"
#include "View/SlotViewWidget.h"
#include "UPMainHudWidget.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPORTFOLIO_API UUPMainHudWidget : public UUPUserWidget
{
	GENERATED_BODY()
public:

	const FString HP_PROGRESS_WIDGET_NAME = TEXT("WBP_Pb0");
	const FString MP_PROGRESS_WIDGET_NAME = TEXT("WBP_Pb1");
	
protected:
	const FString PROGRESS_WIDGET_NAME = TEXT("WBP_Pb");
	const int32 SkillSlotMinId = 0;
	const int32 SkillSlotMaxId = 8;

	const int32 ItemSlotMinId = 9;
	const int32 ItemSlotMaxId = 12;

	const int32 ProgressMinId = 0;
	const int32 ProgressMaxId = 1;

	
	
	virtual void NativeConstruct() override;
	
	UPROPERTY(EditAnywhere , Category = Widget)
	TArray<TObjectPtr<USlotViewWidget>> SkillSlotViewArray;

	UPROPERTY(EditAnywhere , Category = Widget)
	TArray<TObjectPtr<UItemSlotViewWidget>> ItemSlotViewArray;

	UPROPERTY(EditAnywhere , Category = Widget)
	TObjectPtr<UProgressViewWidget> HpProgressView;

	UPROPERTY(EditAnywhere , Category = Widget)
	TObjectPtr<UProgressViewWidget> MpProgressView;
	
public:
	TArray<TObjectPtr<USlotViewWidget>> GetSkillSlotArray();
	TObjectPtr<USlotViewWidget> GetSlotViewWidgetByActionId(int32 ActionId);
	void SetProgress(AActor* Owner);
};
