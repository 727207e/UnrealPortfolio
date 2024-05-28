// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "UPLevelScriptActor.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPORTFOLIO_API AUPLevelScriptActor : public ALevelScriptActor
{
	GENERATED_BODY()
	
public :
	AUPLevelScriptActor();

	UPROPERTY()
	FTimerHandle LevelLoadStartTimeHandle;
	UPROPERTY()
	FTimerHandle ProgressCheckTimeHandle;
	UPROPERTY()
	FTimerHandle OpenLevelTimeHandle;
	
	UFUNCTION(BlueprintCallable, Category = "LoadLevel")
	void LoadNextLevelByAsync(const FString& NextLevelPath);	//NextLevelPath : /Game/Level/TopDownSampleScene
	void ProgressCheck();

	FString NextLevel;
	
	UPROPERTY(BlueprintReadOnly)
	float ProgressLoad;
	float OldProgressLoad;

	TObjectPtr<class UUPLoadLevelUserWidget> LevelLoadWidget;

private :
	UPROPERTY()
	TObjectPtr<class UWidgetComponent> LevelLoadWidgetComp;

	FString LevelName;
	UFUNCTION()
	void OnLevelLoaded();
};