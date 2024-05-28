// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CutScene/UPCutSceneEvent.h"
#include "UPCutSceneMapOneGenDumyBoss.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPORTFOLIO_API AUPCutSceneMapOneGenDumyBoss : public AUPCutSceneEvent
{
	GENERATED_BODY()
	
public :
	virtual void StartEvent() override;
	virtual void FinishEvent() override;

public :
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ACharacter> DumyBossType;
	ACharacter* DummyBoss;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<AActor> GenPosition;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class ABossManager> BossManager;
};