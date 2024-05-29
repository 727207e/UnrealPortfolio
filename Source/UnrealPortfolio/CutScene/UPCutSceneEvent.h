// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Game/BossManager.h"
#include "UPCutSceneEvent.generated.h"

UCLASS()
class UNREALPORTFOLIO_API AUPCutSceneEvent : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUPCutSceneEvent();

	virtual void BeginPlay() override;
	virtual void StartEvent();
	virtual void FinishEvent();

protected :
	UPROPERTY()
	TObjectPtr<ABossManager> BossManager;
};