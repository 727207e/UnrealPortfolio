// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ProgressWidgetModelData.generated.h"

USTRUCT(BlueprintType)
struct FProgressWidgetModelData : public FTableRowBase
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	FLinearColor ProgressFillColor = FLinearColor::Black;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	FLinearColor ProgressBgColor = FLinearColor::Black;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	float Duration = 0;
};
