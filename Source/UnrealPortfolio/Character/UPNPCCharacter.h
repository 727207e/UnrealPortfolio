// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/UPEntityInterface.h"
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
class UNREALPORTFOLIO_API AUPNPCCharacter : public ACharacter ,public IUPUINpcInterface, public IUPEntityInterface
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
	virtual	 FTransform GetNPCCameraTransform() override;
	virtual  void LookTarget(const FVector& TargetLocation) override;
	virtual  FVector GetCurLocation() override;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class USceneComponent> NPCCameraTransform;

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
