// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "UPActionTable.generated.h"

USTRUCT(BlueprintType)
struct FUPActionTable : public FTableRowBase
{
	GENERATED_BODY()

public:
	FUPActionTable() : Id(0),NockbackSize(1000),ActionName(TEXT("None")) {};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	int32 Id = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	float NockbackSize = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	float NockbackDuration = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	float NockbackUpSize = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	FString ActionName;

	
};