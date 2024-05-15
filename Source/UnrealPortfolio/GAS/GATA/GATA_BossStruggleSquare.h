// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAS/GATA/GATA_SquareTrace.h"
#include "GATA_BossStruggleSquare.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPORTFOLIO_API AGATA_BossStruggleSquare : public AGATA_SquareTrace
{
	GENERATED_BODY()
	
public :
	AGATA_BossStruggleSquare();

	UPROPERTY(EditAnywhere)
	float BoxSizeXValue;

	UPROPERTY(EditAnywhere)
	float BoxSizeYValue;

protected :
	virtual void GetAttributeSetting() override;
	virtual void DrawDecal() override;
};
