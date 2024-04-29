
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Data/DataAsset/UPBaseTable.h"
#include "UPNormalEnemyTable.generated.h"

USTRUCT(BlueprintType)
struct FUPNormalEnemyTable : public FUPBaseTable
{
	GENERATED_BODY()

public:
	FUPNormalEnemyTable() : FleezeTime(0.0f), TargetSearchingRange(0.0f) {}
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float FleezeTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float TargetSearchingRange;
};