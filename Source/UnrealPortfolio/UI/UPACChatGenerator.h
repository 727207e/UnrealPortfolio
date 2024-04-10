// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UPACChatGenerator.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALPORTFOLIO_API UUPACChatGenerator : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UUPACChatGenerator();
	
	UPROPERTY(VisibleAnywhere, Category = UI)
	TSubclassOf<class UUPChatUIUserWidget> ChatUIWidget;

	class UUPChatUIUserWidget* ChatUIBP;
	class UUPBoxChatUserWidget* ChatBoxWidget;
	
	void FocusChat();
	void Scroll(bool bUp);

	UFUNCTION(BlueprintCallable, Server, Unreliable)
	void SendMessageToServer(const FString& Message);

	UFUNCTION(Client, Unreliable)
	void AddChatMessageOnOwningClient(const FString& Message);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
};
