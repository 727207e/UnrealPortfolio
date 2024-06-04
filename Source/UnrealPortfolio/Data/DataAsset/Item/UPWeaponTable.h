#pragma once

#include "CoreMinimal.h"
#include "UPItemTable.h"
#include "Engine/DataTable.h"
#include "UPWeaponTable.generated.h"


USTRUCT(BlueprintType)
struct FUPWeaponTable : public FUPItemTable
{
	GENERATED_BODY()

	FUPWeaponTable() : Grade(0) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
	TObjectPtr<UStaticMesh> Mesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	int32 Grade = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GAS)
	int32 WeaponLevel = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GAS)
	int32 LegendLevel = 0;
	
};