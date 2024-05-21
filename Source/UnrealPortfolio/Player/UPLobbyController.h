// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
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
	TObjectPtr<class UUPACLobbyUIHelper> LobbyUIHelperComponent;
};
