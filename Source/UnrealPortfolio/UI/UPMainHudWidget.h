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
	UUPMainHudWidget();

public:
	TTuple<bool, TObjectPtr<USlotViewWidget>>  GetLastBuffViewWidget(int32 CastingBuffId);

	void SetProgress(AActor* Owner);
	void BuffProcess();

	void TargetButtonPress(int32 TargetIndex, int32 TargetCoolDown);

public:
	const FString HP_PROGRESS_WIDGET_NAME = TEXT("WBP_Pb0");
	const FString MP_PROGRESS_WIDGET_NAME = TEXT("WBP_Pb1");

	UFUNCTION(BlueprintImplementableEvent, Category = "Inventory")
	void ItemGamePlayEffect(int32 Index);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UGameplayEffect> GetGameplayEffect;

protected:
	const FString PROGRESS_WIDGET_NAME = TEXT("WBP_Pb");
	const FString WIDGET_BUFF_VIEW  = TEXT("BuffSlot");
	
	const int32 SkillSlotMinId = 0;
	const int32 SkillSlotMaxId = 8;
	
	const int32 ItemSlotMinId = 9;
	const int32 ItemSlotMaxId = 12;

	const int32 ProgressMinId = 0;
	const int32 ProgressMaxId = 1;

	TObjectPtr<USlotViewWidget> GetSlotViewWidgetByActionId(int32 ActionId);

	virtual void NativeConstruct() override;
	
	UPROPERTY(EditAnywhere , Category = Widget)
	TArray<TObjectPtr<USlotViewWidget>> SkillSlotViewArray;

	UPROPERTY(EditAnywhere , Category = Widget)
	TArray<TObjectPtr<USlotViewWidget>> BuffSlotViewArray;
	
	UPROPERTY(EditAnywhere , Category = Widget)
	TArray<TObjectPtr<UItemSlotViewWidget>> ItemSlotViewArray;

	UPROPERTY(EditAnywhere , Category = Widget)
	TObjectPtr<UProgressViewWidget> HpProgressView;

	UPROPERTY(EditAnywhere , Category = Widget)
	TObjectPtr<UProgressViewWidget> MpProgressView;

	UPROPERTY(EditAnywhere , Category = Widget)
	TSubclassOf<class USlotViewWidget> BuffViewer;

};