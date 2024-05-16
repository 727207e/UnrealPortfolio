// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAS/GATA/GATA_SkillTrace.h"
#include "GATA_HalfCircleTrace.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPORTFOLIO_API AGATA_HalfCircleTrace : public AGATA_SkillTrace
{
	GENERATED_BODY()

public :
	AGATA_HalfCircleTrace();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class UBoxComponent> Cube;

	virtual void DrawDecal() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class UDecalComponent> LeftHalfDecal;
protected :
	virtual FGameplayAbilityTargetDataHandle MakeTargetData() const override;
};