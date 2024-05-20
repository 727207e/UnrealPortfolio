// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/UPLobbyController.h"
#include "UI/UPLobbyHUDWidget.h"

AUPLobbyController::AUPLobbyController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
}

void AUPLobbyController::BeginPlay()
{	
	Super::BeginPlay();

	if (nullptr != LobbyHUDWidgetType)
	{
		LobbyHUDWidget = CastChecked<UUPLobbyHUDWidget>(CreateWidget(GetWorld(), LobbyHUDWidgetType, TEXT("LobbyHUDWidgetType")));
		LobbyHUDWidget->AddToViewport();
	}

}

void AUPLobbyController::TryConnectToServer(const FString& Address)
{
	ConsoleCommand("open " + Address);
	GetWorld()->GetTimerManager().SetTimer(IPCheckTimerHandle, this, &AUPLobbyController::CheckIPAddress, 3.0f, false);
}

void AUPLobbyController::CheckIPAddress()
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
