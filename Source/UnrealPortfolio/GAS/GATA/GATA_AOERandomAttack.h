// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAS/GATA/GATA_SkillTrace.h"
#include "GATA_AOERandomAttack.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPORTFOLIO_API AGATA_AOERandomAttack : public AGATA_SkillTrace
{
	GENERATED_BODY()
	
public :
	AGATA_AOERandomAttack();

protected:
	virtual FGameplayAbilityTargetDataHandle MakeTargetData() const override;
	virtual TArray<FVector> GetRandomRadiusPosition() const;

private :
	float SearchingRadius = 0;
};
