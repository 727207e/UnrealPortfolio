// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/UPUserWidget.h"
#include "UPBoxChatUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPORTFOLIO_API UUPBoxChatUserWidget : public UUPUserWidget
{
	GENERATED_BODY()
	
public :
	UFUNCTION(BlueprintNativeEvent)
	void FocusChat();
	virtual void FocusChat_Implementation();
	
	UFUNCTION(BlueprintNativeEvent)
	void Scroll(bool bUp);
	virtual void Scroll_Implementation(bool bUp);
	
	UFUNCTION(BlueprintNativeEvent)
	void AddChatMessage(const FString& Message);
	virtual void AddChatMessage_Implementation(const FString& Message);
};
