// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAS/GATA/GATA_BossStruggleSphere.h"
#include "GATA_BossStruggleDoubleSphere.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPORTFOLIO_API AGATA_BossStruggleDoubleSphere : public AGATA_BossStruggleSphere
{
	GENERATED_BODY()
	
public :
	AGATA_BossStruggleDoubleSphere();

	virtual void SearchAllTarget() override;

protected:
	virtual void SpawnGC(FVector TargetSpawnLocation) override;


	UPROPERTY(EditAnywhere)
	float InnerSphereScaleValue;
};
