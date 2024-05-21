// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UPPersistentHUDWidget.h"
#include "Player/UPPersistentController.h"
#include "Game/UPGameInstance.h"

void UUPPersistentHUDWidget::OnBtnConnectToServer(const FString& Address)
{
	TArray<FString> Words;
	Address.ParseIntoArray(Words, TEXT("."), true);

	if (Words.Num() != 4)
	{
		UE_LOG(LogTemp, Error, TEXT("UUPPersistentHUDWidget : It's Not IP Address"));
		return;
	}

	for (const FString& Word : Words)
	{
		if (!Word.IsNumeric())
		{
			UE_LOG(LogTemp, Error, TEXT("UUPPersistentHUDWidget : It's Not IP Address"));
			return;
		}

		int32 WordValue = FCString::Atoi(*Word);
		
		if (WordValue < 0 || WordValue > 256)
		{
			UE_LOG(LogTemp, Error, TEXT("UUPPersistentHUDWidget : It's Not IP Address"));
			return;
		}
	}

	AUPPersistentController* PersistentController = Cast<AUPPersistentController>(GetWorld()->GetFirstPlayerController());
	if (PersistentController)
	{
		PersistentController->TryConnectToServer(Address);
	}
}

void UUPPersistentHUDWidget::OnSettingUserNickname(const FString& Nickname)
{
	UUPGameInstance* GameInstance = Cast< UUPGameInstance>(GetWorld()->GetGameInstance());
	if (GameInstance)
	{
		GameInstance->PlayerNickname = Nickname;
	}
}
