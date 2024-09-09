// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/UPPersistentController.h"
#include "Blueprint/UserWidget.h"
#include "UI/UPLobbyHUDWidget.h"

AUPPersistentController::AUPPersistentController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
}

void AUPPersistentController::BeginPlay()
{
	Super::BeginPlay();

	if (nullptr != PersistentHUDWidgetType)
	{
		PersistentHudWidget = CreateWidget(GetWorld(), PersistentHUDWidgetType, TEXT("UUPPersistentHUDWidget"));
		PersistentHudWidget->AddToViewport();
	}
}

void AUPPersistentController::TryConnectToServer(const FString& Address)
{
	ConsoleCommand("open " + Address);
	GetWorld()->GetTimerManager().SetTimer(IPCheckTimerHandle, this, &AUPPersistentController::ConnectTimeOver, 5.0f, false);
}

void AUPPersistentController::ConnectTimeOver()
{
	if (GetWorld() && GetWorld()->GetNetDriver())
	{
		GetWorld()->GetNetDriver()->Shutdown();
	}
	if (IsLocalPlayerController())
	{
		GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
	}
}
