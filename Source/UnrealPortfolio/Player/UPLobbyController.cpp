// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/UPLobbyController.h"
#include "Blueprint/UserWidget.h"
#include "UI/UPACLobbyUIHelper.h"
#include "UI/UPLobbyHUDWidget.h"

AUPLobbyController::AUPLobbyController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	LobbyUIHelperComponent = CreateDefaultSubobject<UUPACLobbyUIHelper>(TEXT("LobbyUIHelperComponent"));
}