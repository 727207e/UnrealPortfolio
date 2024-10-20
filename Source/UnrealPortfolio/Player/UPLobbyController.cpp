// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/UPLobbyController.h"
#include "Blueprint/UserWidget.h"
#include "UI/UPLobbyHUDWidget.h"
#include "Game/UPGameInstance.h"
#include "Game/UPLobbyGameState.h"

AUPLobbyController::AUPLobbyController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	static ConstructorHelpers::FClassFinder<UUPLobbyHUDWidget> LobbyHUDWidgetTypeRef(TEXT("/Game/UI/Lobby/WBP_LobbyHUD.WBP_LobbyHUD_C"));
	LobbyHUDWidgetType = LobbyHUDWidgetTypeRef.Class;
}

void AUPLobbyController::BeginPlay()
{
	Super::BeginPlay();

	LobbyGameState = Cast<AUPLobbyGameState>(GetWorld()->GetGameState());
	if (!IsLocalController())
	{
		return;
	}

	UUPGameInstance* GameInstance = Cast<UUPGameInstance>(GetWorld()->GetGameInstance());
	if (GameInstance)
	{
		MyUserData.NickName = GameInstance->PlayerNickname;
		LobbyHUDWidget = Cast<UUPLobbyHUDWidget>(CreateWidget(GetWorld(), LobbyHUDWidgetType));
		LobbyHUDWidget->AddToViewport();
		LobbyHUDWidget->InitLobbyHud();
	}

	if (HasAuthority())
	{
		if (LobbyGameState)
		{
			LobbyGameState->AddUserData(MyUserData);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("UPLobbyController Server : Can't BeginPlay , No LobbyGameState"));
			return;
		}
	}
	else
	{
		Server_UpdateUserData(MyUserData);
	}
}

void AUPLobbyController::Server_UpdateUserData_Implementation(const FUPUserData& UserData)
{
	if (LobbyGameState)
	{
		MyUserData = UserData;
		LobbyGameState->AddUserData(UserData);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("UPLobbyController Server : Can't UpdateUserData , No LobbyGameState"));
		return;
	}
}

void AUPLobbyController::Server_SetPlayerReady_Implementation(uint8 bIsReady)
{
	MyUserData.bIsReady = bIsReady;
	UserDataUpdate();
}

void AUPLobbyController::SetPlayerReady()
{
	MyUserData.bIsReady = MyUserData.bIsReady == 0 ? 1 : 0;
	Server_SetPlayerReady(MyUserData.bIsReady);
}

void AUPLobbyController::Server_SetPlayerClass_Implementation(CharacterClass TargetClass)
{
	MyUserData.ThisCharacterClass = TargetClass;
	UserDataUpdate();
}

void AUPLobbyController::SetPlayerClass(CharacterClass TargetClass)
{
	MyUserData.ThisCharacterClass = TargetClass;
	Server_SetPlayerClass(TargetClass);
}

void AUPLobbyController::Server_TryPlayStart_Implementation()
{
	if (LobbyGameState)
	{
		LobbyGameState->MoveNextLevel("/Game/Level/Village");
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("UPLobbyController Server : Can't Server_TryPlayStart , No LobbyGameState"));
		return;
	}
}

void AUPLobbyController::TryPlayStart()
{
	if (MyUserData.bIsReady == 1)
	{
		Server_TryPlayStart();
	}
}

void AUPLobbyController::UserDataUpdate()
{
	if (LobbyGameState)
	{
		LobbyGameState->ChangeUserData(MyUserData);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("UPLobbyController Server : Can't UserDataUpdate , No LobbyGameState"));
		return;
	}
}