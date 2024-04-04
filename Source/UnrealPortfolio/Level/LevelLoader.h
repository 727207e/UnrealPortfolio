// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelLoader.generated.h"

UCLASS()
class UNREALPORTFOLIO_API ALevelLoader : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALevelLoader();

	virtual void BeginPlay() override;
	
	UPROPERTY()
	FTimerHandle Handle;
	
	UPROPERTY()
	FTimerHandle Handle2;
	UPROPERTY()
	FTimerHandle Handle3;

	UFUNCTION()
	void LoadLevelDebug();


	bool IsDoneCheckReady = false;

private :
	
	UFUNCTION()
	void OpenLevel();

	UFUNCTION()
	void ProgressCheck();

};
