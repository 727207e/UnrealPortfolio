// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/UPUserWidget.h"
#include "View/SlotViewWidget.h"
#include "UPMainHudWidget.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPORTFOLIO_API UUPMainHudWidget : public UUPUserWidget
{
	GENERATED_BODY()
protected:
	const int32 SkillSlotMinId = 0;
	const int32 SkillSlotMaxId = 8;
	
	virtual void NativeConstruct() override;
	
	UPROPERTY(EditAnywhere , Category = Widget)
	TArray<TObjectPtr<USlotViewWidget>> SkillSlotViewArray;
	
	UPROPERTY(EditAnywhere , Category = Widget)
	TArray<TObjectPtr<USlotViewWidget>> ItemSlotViewArray;
public:
	TArray<TObjectPtr<USlotViewWidget>> GetSkillSlotArray();
	TObjectPtr<USlotViewWidget> GetSlotViewWidgetByActionId(int32 ActionId);
	
};
