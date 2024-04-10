// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/UPUserWidget.h"
#include "UPChatUIUserWidget.generated.h"

class UUPBoxChatUserWidget;

/**
 * 
 */
UCLASS()
class UNREALPORTFOLIO_API UUPChatUIUserWidget : public UUPUserWidget
{
	GENERATED_BODY()
	
public :
	
	UPROPERTY(BlueprintReadWrite)
	class UUPBoxChatUserWidget* ChatBoxWidget;

	UFUNCTION(BlueprintNativeEvent)
	void InitChatBoxWidget();
	virtual void InitChatBoxWidget_Implementation();
};
