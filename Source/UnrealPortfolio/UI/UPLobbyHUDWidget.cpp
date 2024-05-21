// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UPLobbyHUDWidget.h"
#include "Interfaces/IPv4/IPv4Endpoint.h"
#include "Sockets.h"
#include "SocketSubsystem.h"
#include "IPAddress.h"
#include "Engine/World.h"
#include "Game/UPLobbyGameState.h"
#include "Game/UPGameInstance.h"

FString UUPLobbyHUDWidget::GetIPAddress()
{
    bool bCanBindAll;
    TSharedRef<FInternetAddr> Addr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->GetLocalHostAddr(*GLog, bCanBindAll);

    if (Addr->IsValid())
    {
        return Addr->ToString(false);
    }
    else
    {
        return FString();
    }
}

void UUPLobbyHUDWidget::UpdateUserInfo()
{
    
}

void UUPLobbyHUDWidget::InitLobbyHud_Implementation()
{

}

void UUPLobbyHUDWidget::AddUpdateEventToGameState()
{
    AUPLobbyGameState* GameState = Cast<AUPLobbyGameState>(GetWorld()->GetGameState());
    if (GameState)
    {
        GameState->OnPlayerDataListChanged.AddUObject(this, &UUPLobbyHUDWidget::AddUserDataInfoArray);
    }
}


void UUPLobbyHUDWidget::AddUserDataInfo_Implementation(const FUPUserData& NickName)
{
}

void UUPLobbyHUDWidget::AddUserDataInfoArray_Implementation(const TArray<FUPUserData>& PlayerList)
{
}
