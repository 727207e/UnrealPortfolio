// Fill out your copyright notice in the Description page of Project Settings.
#include "UI/Componenet/WidgetHUDComponent.h"
#include "UI/UPMainHudWidget.h"

UWidgetHUDComponent::UWidgetHUDComponent()
{
	static ConstructorHelpers::FClassFinder<UUPMainHudWidget> ChatUIWidgetRef(TEXT("/Game/UI/WBP_Hud.WBP_Hud_C"));
	HudWidgetClass = ChatUIWidgetRef.Class;
	
}
