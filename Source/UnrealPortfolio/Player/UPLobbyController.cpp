// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/UPLobbyController.h"
#include "Blueprint/UserWidget.h"
#include "UI/UPACLobbyUIHelper.h"
#include "UI/UPLobbyHUDWidget.h"
#include "Game/UPGameInstance.h"
#include "Game/UPLobbyGameState.h"
#include "defines/UPServerLogDefine.h"

AUPLobbyController::AUPLobbyController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	static ConstructorHelpers::FClassFinder<UUPLobbyHUDWidget> LobbyHUDWidgetTypeRef(TEXT("/Game/UI/Lobby/WBP_LobbyHUD.WBP_LobbyHUD_C"));
	LobbyHUDWidgetType = LobbyHUDWidgetTypeRef.Class;
}

void AUPLobbyController::BeginPlay()
{
	if (!IsLocalController())
	{
		return;
	}

	UUPGameInstance* GameInstance = Cast<UUPGameInstance>(GetWorld()->GetGameInstance());
	if (GameInstance)
	{
		MyUserData = FUPUserData(GameInstance->PlayerNickname);
		LobbyHUDWidget = Cast<UUPLobbyHUDWidget>(CreateWidget(GetWorld(), LobbyHUDWidgetType));
		LobbyHUDWidget->AddToViewport();
		LobbyHUDWidget->InitLobbyHud();
	}

	if (HasAuthority())
	{
		AUPLobbyGameState* GameState = Cast<AUPLobbyGameState>(GetWorld()->GetGameState());
		if (GameState)
		{
			GameState->AddUserData(MyUserData);
		}
	}
	else
	{
		UE_SERVER_LOG(LogUPNetwork, Error, TEXT("%s"), *MyUserData.NickName);
		Server_UpdateUserData(MyUserData);
	}
}


void AUPLobbyController::Server_UpdateUserData_Implementation(const FUPUserData& UserData)
{
	UE_SERVER_LOG(LogUPNetwork, Error, TEXT("%s"), *UserData.NickName);
	AUPLobbyGameState* GameState = Cast<AUPLobbyGameState>(GetWorld()->GetGameState());
	if (GameState)
	{
		GameState->AddUserData(UserData);
	}
}