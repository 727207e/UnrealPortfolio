
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "UPBossSkillTable.generated.h"

USTRUCT(BlueprintType)
struct FUPBossSkillTable : public FTableRowBase
{
	GENERATED_BODY()

public:
	FUPBossSkillTable() : Damage(0.0f), AttackNumber(0.0f), KnockBack(0.0f), AttackRange(0.0f), AttackSpeed(0.0f), AttackRadius(0.0f) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float AttackNumber;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float KnockBack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float AttackRange;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float AttackSpeed;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float AttackRadius;
};