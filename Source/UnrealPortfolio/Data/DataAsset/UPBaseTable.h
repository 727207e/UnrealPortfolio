
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "UPBaseTable.generated.h"

USTRUCT(BlueprintType)
struct FUPBaseTable : public FTableRowBase
{
	GENERATED_BODY()

public:
	FUPBaseTable() : MaxHp(0.0f), Attack(0.0f), AttackRange(0.0f), AttackSize(0.0f), Armor(0.0f), AttackSpeed(0.0f), AttackRate(0.0f) , MovementSpeed(0.0f) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float MaxHp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float Attack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float AttackRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float AttackSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float Armor;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float AttackSpeed;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float AttackRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float MovementSpeed;

	FUPBaseTable operator+(const FUPBaseTable& Other) const
	{
		const float* const ThisPtr = reinterpret_cast<const float* const>(this);
		const float* const OtherPtr = reinterpret_cast<const float* const>(&Other);

		FUPBaseTable Result;
		float* ResultPtr = reinterpret_cast<float*>(&Result);
		int32 StatNum = sizeof(FUPBaseTable) / sizeof(float);
		for (int32 i = 0; i < StatNum; i++)
		{
			ResultPtr[i] = ThisPtr[i] + OtherPtr[i];
		}

		return Result;
	}
};