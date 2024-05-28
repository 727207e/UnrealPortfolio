// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Game/UpGameState.h"
#include "UPLobbyGameState.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnPlayerDataListChanged, const TArray<FUPUserData>&);

/**
 * 
 */
UCLASS()
class UNREALPORTFOLIO_API AUPLobbyGameState : public AUPGameState
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
    virtual void MoveNextLevel(FString LevelPath) override;

    FOnPlayerDataListChanged OnPlayerDataListChanged;

protected:
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
    virtual void MoveNextLevelAllUser() override;

};
