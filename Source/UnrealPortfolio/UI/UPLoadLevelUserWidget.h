// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/UPUserWidget.h"
#include "UPLoadLevelUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPORTFOLIO_API UUPLoadLevelUserWidget : public UUPUserWidget
{
	GENERATED_BODY()
	
public :
	UPROPERTY(BlueprintReadWrite, Category = LoadProgress)
	float ProgressValue;
};
