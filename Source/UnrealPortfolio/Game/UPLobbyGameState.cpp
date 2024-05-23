// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/UPLobbyGameState.h"
#include "Net/UnrealNetwork.h"

AUPLobbyGameState::AUPLobbyGameState()
{
    bReplicates = true;
}

void AUPLobbyGameState::OnRep_PlayerDataList()
{
    OnPlayerDataListChanged.Broadcast(PlayerDataList);
}

void AUPLobbyGameState::AddUserData(const FUPUserData& UserData)
{
    if (HasAuthority())
    {
        PlayerDataList.Add(UserData);
        OnRep_PlayerDataList();
    }
}

void AUPLobbyGameState::ChangeUserData(const FUPUserData& UserData)
{
    if (HasAuthority())
    {
        for (FUPUserData& TheUserData : PlayerDataList)
        {
            if (TheUserData.NickName == UserData.NickName)
            {
                TheUserData.bIsReady = UserData.bIsReady;
                TheUserData.ThisCharacterClass = UserData.ThisCharacterClass;

                OnRep_PlayerDataList();
                return;
            }
        }

        UE_LOG(LogTemp, Error, TEXT("UPLobbyGameState : Can't Find User NickName"));
        return;
    }
}

void AUPLobbyGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(AUPLobbyGameState, PlayerDataList);
}
