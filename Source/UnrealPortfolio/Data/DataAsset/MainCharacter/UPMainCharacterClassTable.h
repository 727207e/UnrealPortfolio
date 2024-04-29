// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Data/DataAsset/UPBaseTable.h"
#include "UPMainCharacterClassTable.generated.h"

UENUM(BlueprintType)
enum EMainCharacterType : uint8
{
	MaleBarbarian UMETA(DisplayName = "Male Barbarian"),
	FemaleBarbarian UMETA(DisplayName = "Female Barbarian"),
	Rogue UMETA(DisplayName = "Rogue"),
	Shaman UMETA(DisplayName = "Shaman"),
};


USTRUCT(BlueprintType)
struct FUPMainCharacterClassTable : public FUPBaseTable
{
	GENERATED_BODY()
	FUPMainCharacterClassTable() : FreezeTime(0.0f), Mp(0.0f) , MaxMp(0.0f),CharacterType(EMainCharacterType::FemaleBarbarian) {}
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float FreezeTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float Mp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float MaxMp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Type)
	TEnumAsByte<EMainCharacterType> CharacterType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
	TObjectPtr<USkeletalMesh> Mesh;
};