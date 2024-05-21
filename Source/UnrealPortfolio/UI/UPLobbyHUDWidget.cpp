// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UPLobbyHUDWidget.h"
#include "Interfaces/IPv4/IPv4Endpoint.h"
#include "Sockets.h"
#include "SocketSubsystem.h"
#include "IPAddress.h"
#include "Engine/World.h"
#include "Game/UPGameInstance.h"
#include "UI/UPACLobbyUIHelper.h"

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

void UUPLobbyHUDWidget::InitLobbyHud_Implementation()
{
}

void UUPLobbyHUDWidget::AddUserDataInfo_Implementation(const FString& NickName)
{
}

void UUPLobbyHUDWidget::CallUpdateMyInfoToServer(const FString& NickName)
{
    if (ACLobbyUIHelper)
    {
        ACLobbyUIHelper->UpdateUserInfo(NickName);
    }
}
