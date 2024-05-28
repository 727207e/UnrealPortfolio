// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "UPBaseController.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPORTFOLIO_API AUPBaseController : public APlayerController
{
	GENERATED_BODY()
	
public :
	virtual void BeginPlay() override;

	UFUNCTION(Server, Unreliable)
	void Server_AnnounceLevelLoadDone();
	void AnnounceLevelLoadDone();

protected :
	class AUPGameState* UpGameState;
};
