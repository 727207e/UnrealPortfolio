
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Data/DataAsset/UPBaseTable.h"
#include "UPBossTable.generated.h"

USTRUCT(BlueprintType)
struct FUPBossTable : public FUPBaseTable
{
	GENERATED_BODY()

public:
	FUPBossTable() : FleezeTime(0.0f) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float FleezeTime;
};