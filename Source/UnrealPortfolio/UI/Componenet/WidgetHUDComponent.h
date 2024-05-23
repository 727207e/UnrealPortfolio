// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "WidgetHUDComponent.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPORTFOLIO_API UWidgetHUDComponent : public UWidgetComponent
{
	GENERATED_BODY()
public:
	UWidgetHUDComponent();
	UPROPERTY(VisibleAnywhere, Category = UI)
	TSubclassOf<class UUPMainHudWidget> HudWidgetClass;

	UPROPERTY()
	TObjectPtr<class UUPMainHudWidget> MainHudWidget;
};
