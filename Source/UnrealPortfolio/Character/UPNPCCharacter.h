// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/UPUINpcInterface.h"
#include "UPNPCCharacter.generated.h"

DECLARE_DELEGATE(FOnShowNPCWidgetDelegate);

UENUM(BlueprintType)
enum class ENPCWidgetType : uint8
{
	WeaponShop UMETA(DisplayName = "WeaponShop"),
	ItemShop UMETA(DisplayName = "ItemShop"),
	RaidSelector UMETA(DisplayName = "RaidSelector"),
};

USTRUCT(BlueprintType)
struct FTakeWidgetDelegateWrapper
{
	GENERATED_BODY()
	FTakeWidgetDelegateWrapper(){}
	FTakeWidgetDelegateWrapper(const FOnShowNPCWidgetDelegate& Delegate) : OnTakeWidget(Delegate) {}

	FOnShowNPCWidgetDelegate OnTakeWidget;
};



UCLASS()
class UNREALPORTFOLIO_API AUPNPCCharacter : public ACharacter ,public IUPUINpcInterface
{
	GENERATED_BODY()

public:
	AUPNPCCharacter();
public:
	UPROPERTY(EditAnywhere, Category = NPC)
	ENPCWidgetType widgetType;
	TArray<FTakeWidgetDelegateWrapper> TakeUiActions;
public:
	UFUNCTION()
	virtual  void TakeNPCWidgetShow() override;
	virtual  void TakeNPCWidgetHide() override;

	virtual  void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = Level)
	FString NextLevelPath;

protected:
	void ShowWeaponShopWidget();
	void ShowItemShopWidget();
	void ShowRaiderSelector();

protected:
	UPROPERTY(VisibleAnywhere, Category = UI)
	TObjectPtr<class UWidgetComponent> InteractionAlarmCompo;
public:
	UFUNCTION(BlueprintCallable)
	void ShowInteractionAlarm();
	UFUNCTION(BlueprintCallable)
	void HideInterActionAlarm();

	
	
};
