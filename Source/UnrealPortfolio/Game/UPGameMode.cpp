// Copyright Epic Games, Inc. All Rights Reserved.

#include "UPGameMode.h"
#include "Player/UPPlayerController.h"
#include "Character/UPCharacter.h"
#include "UObject/ConstructorHelpers.h"

AUPGameMode::AUPGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AUPPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprint/UPCharacter/BP_MainCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// set default controller to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownPlayerController"));
	if (PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
}