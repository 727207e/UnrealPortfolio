// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "UPGameState.generated.h"

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
class UNREALPORTFOLIO_API AUPGameState : public AGameStateBase
{
	GENERATED_BODY()

public :
	AUPGameState();

	UFUNCTION(NetMulticast, Unreliable)
	void NetMulti_LevelLoad(const FString& LevelPath);

    UFUNCTION(BlueprintCallable)
    virtual void MoveNextLevel(FString LevelPath);

    virtual void BeginPlay() override;
    virtual void MoveNextLevelAllUser();

public :
    class UUPGameInstance* UpGameInstance;

protected :

    FString NextLevelPath = "";

private:
    int32 ReadyUserNumber = 0;
};
