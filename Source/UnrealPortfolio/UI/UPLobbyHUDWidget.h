// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Game/UPLobbyGameState.h"
#include "UPLobbyHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPORTFOLIO_API UUPLobbyHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public :
	UFUNCTION(BlueprintCallable)
	FString GetIPAddress();

	UFUNCTION(BlueprintCallable)
	void UpdateUserInfo();

	UFUNCTION(BlueprintCallable)
	void AddUpdateEventToGameState();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void InitLobbyHud();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void AddUserDataInfo(const FUPUserData& NickName);
	virtual void AddUserDataInfo_Implementation(const FUPUserData& NickName);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void AddUserDataInfoArray(const TArray<FUPUserData>& PlayerList);
	virtual void AddUserDataInfoArray_Implementation(const TArray<FUPUserData>& PlayerList);
};
