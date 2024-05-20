// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UPLobbyHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPORTFOLIO_API UUPLobbyHUDWidget : public UUserWidget
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable)
	void OnBtnConnectToServer(const FString& Address);
	UFUNCTION(BlueprintCallable)
	void OnSettingUserNickname(const FString& Nickname);
};
