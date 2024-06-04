// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "SlotWidgetModelData.generated.h"
USTRUCT(BlueprintType)
struct FSlotWidgetModelData : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	FString SlotName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	FString KeyString;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	FString CountString;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	TObjectPtr<UTexture2D> SlotTexture;	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	TObjectPtr<UTexture2D> IconTexture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	int32 InputActionId = 0;
	
};