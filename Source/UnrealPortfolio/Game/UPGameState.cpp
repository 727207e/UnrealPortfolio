// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/UPGameState.h"
#include "Net/UnrealNetwork.h"
#include "Game/UPGameInstance.h"
#include "Level/UPLevelScriptActor.h"

AUPGameState::AUPGameState()
{
}

void AUPGameState::BeginPlay()
{
    Super::BeginPlay();

    UpGameInstance = Cast<UUPGameInstance>(GetWorld()->GetGameInstance());
    if (nullptr == UpGameInstance)
    {
        UE_LOG(LogTemp, Error, TEXT("UPGameState : Can't Get UpGameInstance"));
        return;
    }
}

void AUPGameState::MoveNextLevel(FString LevelPath)
{
    if (HasAuthority())
    {
        NetMulti_LevelLoad(LevelPath);
    }
}

void AUPGameState::NetMulti_LevelLoad_Implementation(const FString& LevelPath)
{
    NextLevelPath = LevelPath;
    if (NextLevelPath.IsEmpty())
    {
        UE_LOG(LogTemp, Error, TEXT("UPGameState : NextLevelPath is Empty"));
        return;
    }

    AUPLevelScriptActor* UpLevelScript = Cast<AUPLevelScriptActor>(GetWorld()->GetLevelScriptActor());
    if (UpLevelScript)
    {
        UpLevelScript->LoadNextLevelByAsync(NextLevelPath);
    }
}

void AUPGameState::MoveNextLevelAllUser()
{
    ReadyUserNumber++;
    if (ReadyUserNumber >= UpGameInstance->UserNumber)
    {
        CollectGarbage(GARBAGE_COLLECTION_KEEPFLAGS, true);
        GetWorld()->ServerTravel(NextLevelPath);
    }
}