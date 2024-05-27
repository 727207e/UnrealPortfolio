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
	
public:
	UPROPERTY()
	TObjectPtr<class AUPLobbyGameState> LobbyGameState;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game State")
	FUPUserData MyUserData;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> LobbyHUDWidgetType;
	UPROPERTY()
	TObjectPtr<class UUPLobbyHUDWidget> LobbyHUDWidget;

	UFUNCTION()
	void UserDataUpdate();

	UFUNCTION(Server, Unreliable)
	void Server_UpdateUserData(const FUPUserData& UserData);

	UFUNCTION(Server, Unreliable)
	void Server_SetPlayerReady(uint8 bIsReady);
	void SetPlayerReady();

	UFUNCTION(Server, Unreliable)
	void Server_SetPlayerClass(CharacterClass TargetClass);
	void SetPlayerClass(CharacterClass TargetClass);

	UFUNCTION(Server, Unreliable)
	void Server_TryPlayStart();
	void TryPlayStart();

	UFUNCTION(Server, Unreliable)
	void Server_AnnounceLevelLoadDone();
	void AnnounceLevelLoadDone();
};