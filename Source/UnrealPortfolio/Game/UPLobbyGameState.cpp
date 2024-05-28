// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/UPLobbyGameState.h"
#include "Net/UnrealNetwork.h"
#include "Kismet/GameplayStatics.h"
#include "Level/UPLevelScriptActor.h"

AUPLobbyGameState::AUPLobbyGameState()
{
    bReplicates = true;
    NextLevelPath = "/Game/Level/Village";
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

void AUPLobbyGameState::TryGamePlayStart()
{
    if (HasAuthority())
    {
        for (FUPUserData TheUserData : PlayerDataList)
        {
            if (TheUserData.bIsReady != 1)
            {
                UE_LOG(LogTemp, Error, TEXT("UPLobbyGameState : User(%s) is not Ready"), *TheUserData.NickName);
                return;
            }
        }

        NetMulti_LevelLoad();
    }
}

void AUPLobbyGameState::MoveNextLevelAllUser()
{
    ReadyUserNumber++;

    if (ReadyUserNumber == PlayerDataList.Num())
    {
        GetWorld()->ServerTravel(NextLevelPath);
    }
}

void AUPLobbyGameState::NetMulti_LevelLoad_Implementation()
{
    AUPLevelScriptActor* UpLevelScript = Cast<AUPLevelScriptActor>(GetWorld()->GetLevelScriptActor());
    if (UpLevelScript)
    {
        UpLevelScript->LoadNextLevelByAsync(NextLevelPath);
    }
}

void AUPLobbyGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(AUPLobbyGameState, PlayerDataList);
}