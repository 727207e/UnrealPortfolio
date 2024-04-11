// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UPACChatGenerator.h"
#include "Misc/OutputDeviceNull.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "Engine/World.h"
#include "GameFramework/GameStateBase.h"
#include "GameFramework/PlayerState.h"
#include "GameFramework/PlayerController.h"
#include "UI/UPChatUIUserWidget.h"
#include "UI/UPBoxChatUserWidget.h"
#include "Components/WidgetComponent.h"

// Sets default values for this component's properties
UUPACChatGenerator::UUPACChatGenerator()
{
	static ConstructorHelpers::FClassFinder<UUPChatUIUserWidget> ChatUIWidgetRef(TEXT("/Game/UI/Chat/WBP_ChatUI.WBP_ChatUI_C"));
	ChatUIWidget = ChatUIWidgetRef.Class;
}


void UUPACChatGenerator::FocusChat()
{
	if (nullptr == ChatBoxWidget)
	{
		return;
	}
	ChatBoxWidget->FocusChat();
}

void UUPACChatGenerator::Scroll(bool bUp)
{
	if (nullptr == ChatBoxWidget)
	{
		return;
	}
	ChatBoxWidget->Scroll(bUp);
}

void UUPACChatGenerator::SendMessageToServer_Implementation(const FString& Message)
{
	for (const auto& player : GetWorld()->GetGameState()->PlayerArray)
	{
		player->GetPlayerController()->GetComponentByClass<UUPACChatGenerator>()->AddChatMessageOnOwningClient(Message);
	}
}

void UUPACChatGenerator::AddChatMessageOnOwningClient_Implementation(const FString& Message)
{
	if (nullptr == ChatBoxWidget)
	{
		return;
	}
	ChatBoxWidget->AddChatMessage(Message);
}

// Called when the game starts
void UUPACChatGenerator::BeginPlay()
{
	APlayerController* OwnerController = Cast<APlayerController>(GetOwner());
	if (OwnerController->IsLocalController())
	{
		ChatUIBP = Cast<UUPChatUIUserWidget>(CreateWidget(GetWorld(), ChatUIWidget));
		ChatUIBP->AddToViewport();
		ChatUIBP->InitChatBoxWidget();
		ChatBoxWidget = ChatUIBP->ChatBoxWidget;
	}
}