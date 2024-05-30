// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/UPBaseController.h"
#include "Game/UPGameState.h"


void AUPBaseController::BeginPlay()
{
	UpGameState = Cast<AUPGameState>(GetWorld()->GetGameState());
	
	Super::BeginPlay();
}

void AUPBaseController::AnnounceLevelLoadDone()
{
	Server_AnnounceLevelLoadDone();
}

void AUPBaseController::Server_AnnounceLevelLoadDone_Implementation()
{
	if (UpGameState)
	{
		UpGameState->MoveNextLevelAllUser();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("UPLobbyController Server : Can't Server_TryPlayStart , No LobbyGameState"));
		return;
	}
}