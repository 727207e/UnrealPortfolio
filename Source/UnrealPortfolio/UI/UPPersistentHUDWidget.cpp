// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UPPersistentHUDWidget.h"
#include "Player/UPLobbyController.h"
#include "Game/UPGameInstance.h"

void UUPPersistentHUDWidget::OnBtnConnectToServer(const FString& Address)
{
	TArray<FString> Words;
	Address.ParseIntoArray(Words, TEXT("."), true);

	if (Words.Num() != 4)
	{
		UE_LOG(LogTemp, Error, TEXT("UPLobbyController : It's Not IP Address"));
		return;
	}

	for (const FString& Word : Words)
	{
		if (!Word.IsNumeric())
		{
			UE_LOG(LogTemp, Error, TEXT("UPLobbyController : It's Not IP Address"));
			return;
		}

		int32 WordValue = FCString::Atoi(*Word);

		// 숫자가 0에서 127 사이인지 확인
		if (WordValue < 0 || WordValue > 127)
		{
			UE_LOG(LogTemp, Error, TEXT("UPLobbyController : It's Not IP Address"));
			return;
		}
	}

	AUPLobbyController* LobbyController = Cast<AUPLobbyController>(GetWorld()->GetFirstPlayerController());
	if (LobbyController)
	{
		LobbyController->TryConnectToServer(Address);
	}
}

void UUPPersistentHUDWidget::OnSettingUserNickname(const FString& Nickname)
{
	UUPGameInstance* GameInstance = Cast< UUPGameInstance>(GetWorld()->GetGameInstance());
	if (GameInstance)
	{
		GameInstance->PlayerNickname = Nickname;


		UE_LOG(LogTemp, Error, TEXT("UserNick : %s"), *GameInstance->PlayerNickname);
	}
}
