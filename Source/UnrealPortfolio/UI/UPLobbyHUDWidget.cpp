// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UPLobbyHUDWidget.h"
#include "Player/UPLobbyController.h"

void UUPLobbyHUDWidget::OnBtnConnectToServer(const FString& Address)
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

		// ���ڰ� 0���� 127 �������� Ȯ��
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