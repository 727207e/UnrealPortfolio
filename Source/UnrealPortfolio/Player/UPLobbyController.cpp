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

	UE_LOG(LogTemp, Error, TEXT("111"));
	if (nullptr != LobbyHUDWidgetType)
	{
		UE_LOG(LogTemp, Error, TEXT("1112222"));
		LobbyHUDWidget = CastChecked<UUPLobbyHUDWidget>(CreateWidget(GetWorld(), LobbyHUDWidgetType, TEXT("LobbyHUDWidgetType")));
		LobbyHUDWidget->AddToViewport();
	}
}