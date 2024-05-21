// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UPACLobbyUIHelper.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALPORTFOLIO_API UUPACLobbyUIHelper : public UActorComponent
{
	GENERATED_BODY()

public:	
	UUPACLobbyUIHelper();
	virtual void BeginPlay() override;

	void UpdateUserInfo(const FString& NickName);
	void UpdateUserInfoSpecific();

	UFUNCTION(Server, Unreliable)
	void Server_UpdateUserInfo(const FString& NickName);
	UFUNCTION(Client, Unreliable)
	void Client_UpdateUserInfo(const FString& NickName);

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> LobbyHUDWidgetType;
	UPROPERTY()
	TObjectPtr<class UUPLobbyHUDWidget> LobbyHUDWidget;

};
