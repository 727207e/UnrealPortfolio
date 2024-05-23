// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "UPLobbyGameState.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnPlayerDataListChanged, const TArray<FUPUserData>&);

UENUM(BlueprintType)
enum class CharacterClass : uint8
{
    Warrior,
    Magician
};


USTRUCT(BlueprintType)
struct FUPUserData
{
    GENERATED_BODY()

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data")
    FString NickName;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data")
    CharacterClass ThisCharacterClass;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data")
    uint8 bIsReady = 0;
};

/**
 * 
 */
UCLASS()
class UNREALPORTFOLIO_API AUPLobbyGameState : public AGameStateBase
{
	GENERATED_BODY()
	
public :
    AUPLobbyGameState();

    UPROPERTY(ReplicatedUsing = OnRep_PlayerDataList, VisibleAnywhere, BlueprintReadOnly, Category = "Game State")
    TArray<FUPUserData> PlayerDataList;

    UFUNCTION()
    void OnRep_PlayerDataList();

    void AddUserData(const FUPUserData& UserData);
    void ChangeUserData(const FUPUserData& UserData);
    void TryGamePlayStart();
    void GamePlayStart();

    FOnPlayerDataListChanged OnPlayerDataListChanged;

protected:
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
