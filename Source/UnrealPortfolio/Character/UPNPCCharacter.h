// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/UPEntityInterface.h"
#include "Interface/UPUINpcInterface.h"
#include "UPNPCCharacter.generated.h"

DECLARE_DELEGATE(FOnShowNPCWidgetDelegate);


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
	TArray<FTakeWidgetDelegateWrapper> TakeUiActions;
public:
	UFUNCTION()
	virtual void TakeNPCWidgetShow() override;
	virtual void TakeNPCWidgetHide() override;

	virtual void BeginPlay() override;
	virtual FTransform GetNPCCameraTransform() override;
	virtual void LookTarget(const FVector& TargetLocation) override;
	virtual FVector GetCurLocation() override;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class USceneComponent> NPCCameraTransform;

	UPROPERTY(EditAnywhere, Category = Level)
	FString NextLevelPath;

	UPROPERTY(EditAnywhere, BlueprintReadwrite)
	TSubclassOf<class UUserWidget> NPCUIType;

	TObjectPtr<class UUserWidget> NPCUI;

protected:
	UPROPERTY(VisibleAnywhere, Category = UI)
	TObjectPtr<class UWidgetComponent> InteractionAlarmCompo;
public:
	UFUNCTION(BlueprintCallable)
	void ShowInteractionAlarm();
	UFUNCTION(BlueprintCallable)
	void HideInterActionAlarm();
};
