// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "UPGameInstance.generated.h"

UCLASS()
class UNREALPORTFOLIO_API UUPGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public :
	UUPGameInstance();

	UPROPERTY()
	FTimerHandle LevelLoadStartTimeHandle;
	UPROPERTY()
	FTimerHandle ProgressCheckTimeHandle;
	UPROPERTY()
	FTimerHandle OpenLevelTimeHandle;
	
	UFUNCTION()
	void LoadNextLevelByAsync(const FString& NextLevelPath);	//NextLevelPath : /Game/Level/TopDownSampleScene

	FString NextLevel;
	bool IsDoneCheckReady = false;

private :
	
	UFUNCTION()
	void OpenLevel();

	UFUNCTION()
	void ProgressCheck();
};
