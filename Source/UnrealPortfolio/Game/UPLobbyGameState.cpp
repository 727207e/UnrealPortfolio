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

void AUPLobbyGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(AUPLobbyGameState, PlayerDataList);
}
