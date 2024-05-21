// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Game/UPLobbyGameState.h"
#include "UPLobbyController.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPORTFOLIO_API AUPLobbyController : public APlayerController
{
	GENERATED_BODY()
	
public :
	AUPLobbyController();

public :
	virtual void BeginPlay() override;
	
public :
	TObjectPtr<class UUPACLobbyUIHelper> LobbyUIHelperComponent;
	FUPUserData MyUserData;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> LobbyHUDWidgetType;
	UPROPERTY()
	TObjectPtr<class UUPLobbyHUDWidget> LobbyHUDWidget;

	UFUNCTION(Server, Unreliable)
	void Server_UpdateUserData(const FUPUserData& UserData);

};
