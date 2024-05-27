// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "UPSkillData.generated.h"


UENUM(BlueprintType)
enum class ESkillType : uint8
{
	Attack UMETA(DisplayName = "Attack"),
	Buff UMETA(DisplayName = "Buff"),
};

USTRUCT(BlueprintType)
struct FUPSkillData : public  FTableRowBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	int32 SKillAbilityIndex;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	TSubclassOf<class UGameplayAbility> TargetGameplayAbility;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	TObjectPtr<UTexture2D> SKillIconTexture;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	float CooldownTime;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	int32 MagicPoints;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	ESkillType SkillType;
};
