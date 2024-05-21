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

public :
	UFUNCTION(BlueprintCallable)
	FString GetIPAddress();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void InitLobbyHud();
	virtual void InitLobbyHud_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void AddUserDataInfo(const FString& NickName);
	virtual void AddUserDataInfo_Implementation(const FString& NickName);

	UPROPERTY()
	TObjectPtr<class UUPACLobbyUIHelper> ACLobbyUIHelper;

	UFUNCTION(BlueprintCallable)
	void CallUpdateMyInfoToServer(const FString& NickName);

};
