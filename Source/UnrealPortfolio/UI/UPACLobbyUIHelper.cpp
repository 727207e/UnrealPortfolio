// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UPACLobbyUIHelper.h"
#include "UI/UPLobbyHUDWidget.h"
#include "Player/UPLobbyController.h"
#include "GameFramework/GameStateBase.h"
#include "GameFramework/PlayerState.h"

UUPACLobbyUIHelper::UUPACLobbyUIHelper()
{
    static ConstructorHelpers::FClassFinder<UUPLobbyHUDWidget> LobbyHUDWidgetTypeRef(TEXT("/Game/UI/Lobby/WBP_LobbyHUD.WBP_LobbyHUD_C"));
    LobbyHUDWidgetType = LobbyHUDWidgetTypeRef.Class;
}

void UUPACLobbyUIHelper::BeginPlay()
{
    Super::BeginPlay();

    APlayerController* OwnerController = Cast<APlayerController>(GetOwner());
    if (OwnerController->IsLocalController())
    {
        LobbyHUDWidget = Cast<UUPLobbyHUDWidget>(CreateWidget(GetWorld(), LobbyHUDWidgetType));
        LobbyHUDWidget->ACLobbyUIHelper = this;
        LobbyHUDWidget->AddToViewport();
        LobbyHUDWidget->InitLobbyHud();
    }
}

void UUPACLobbyUIHelper::UpdateUserInfo(const FString& NickName)
{
    //Server_UpdateUserInfo(NickName);
}

void UUPACLobbyUIHelper::UpdateUserInfoSpecific()
{
}

void UUPACLobbyUIHelper::Server_UpdateUserInfo_Implementation(const FString& NickName)
{
    for (const auto& player : GetWorld()->GetGameState()->PlayerArray)
    {
        player->GetPlayerController()->GetComponentByClass<UUPACLobbyUIHelper>()->Client_UpdateUserInfo(NickName);
    }
}

void UUPACLobbyUIHelper::Client_UpdateUserInfo_Implementation(const FString& NickName)
{
    //LobbyHUDWidget->AddUserDataInfo(NickName);
}
