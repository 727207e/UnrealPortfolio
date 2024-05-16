// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CutScene/UPCutSceneEvent.h"
#include "UPCutSceneBossRun.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPORTFOLIO_API AUPCutSceneBossRun : public AUPCutSceneEvent
{
	GENERATED_BODY()
	
public :
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ACharacter> DumyBossType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<AActor> GenPosition;

	virtual void StartEvent() override;
	virtual void FinishEvent() override;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class ABossManager> BossManager;


protected:
	UPROPERTY()
	TObjectPtr<ACharacter> DumyBoss;

};
