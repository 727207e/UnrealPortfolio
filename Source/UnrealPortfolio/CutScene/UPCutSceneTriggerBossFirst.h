// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CutScene/UPCutSceneTriggerActor.h"
#include "UPCutSceneTriggerBossFirst.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPORTFOLIO_API AUPCutSceneTriggerBossFirst : public AUPCutSceneTriggerActor
{
	GENERATED_BODY()

public :
	AUPCutSceneTriggerBossFirst();

	virtual void BeginPlay() override;
	virtual void PlayNextCutScene() override;

	class UUPGameInstance* UPGameInstance;
};
