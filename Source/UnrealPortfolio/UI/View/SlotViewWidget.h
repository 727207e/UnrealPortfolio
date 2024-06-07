// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Data/DataTable/Widget/SlotWidgetModelData.h"
#include "UI/UPUserWidget.h"
#include "SlotViewWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCooldownFinishDelegate);

UCLASS()
class UNREALPORTFOLIO_API USlotViewWidget : public UUPUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = Slot)
	float CollDownVariableFill;
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = Slot)
	int32 TargetInputActionId;
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = Slot)
	FCooldownFinishDelegate CooldownFinishDelegate;

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = Buff)
	int32 BuffId;
	
public:
	virtual void SetData(const FSlotWidgetModelData& Model);
	virtual void OnClickedTargetInputActionKey(int32 Cooldown);
	
protected:
	virtual void NativeConstruct() override;
	
	UPROPERTY(EditAnywhere, Category = Slot)
	TObjectPtr<class UImage> ImageSlot;

	UPROPERTY(EditAnywhere, Category = Slot)
	TObjectPtr<class UImage> ImageIcon;

	UPROPERTY(EditAnywhere, Category = Slot)
	TObjectPtr<class UTextBlock> TextKey;
	
	UPROPERTY(EditAnywhere, Category = Slot)
	TObjectPtr<class UTextBlock> TextCount;
	
	/** CoolDown Widget **/
	UPROPERTY(EditAnywhere, Category = Slot)
	TObjectPtr<class UImage> ImageCoolDownDimmed;
	UPROPERTY(EditAnywhere, Category = Slot)
	TObjectPtr<class UImage> ImageCoolDownFill;
	UPROPERTY(EditAnywhere, Category = Slot)
	TObjectPtr<class UTextBlock> TextCoolDown;

	
	
protected:
	virtual void StartCooldown(float Cooldown);
	virtual void HiddenCoolDown();
	virtual void ShowCollDown();
	virtual void SetIconSlot(const FSlotWidgetModelData& Model);
	virtual void CooldownEvent();
	float MaxCooldown;
	float CurrentCooldown;
	float DelTime;
	FTimerHandle CooldownTimer;

};

