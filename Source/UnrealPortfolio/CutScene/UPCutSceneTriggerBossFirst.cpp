// Fill out your copyright notice in the Description page of Project Settings.


#include "CutScene/UPCutSceneTriggerBossFirst.h"
#include "Game/UPGameInstance.h"
#include "CutScene/UPCutSceneEvent.h"
#include "Components/BoxComponent.h"

AUPCutSceneTriggerBossFirst::AUPCutSceneTriggerBossFirst()
{
}

void AUPCutSceneTriggerBossFirst::BeginPlay()
{
	Super::BeginPlay();

	UPGameInstance = Cast<UUPGameInstance>(GetWorld()->GetGameInstance());
	if (nullptr == UPGameInstance)
	{
		UE_LOG(LogTemp, Error, TEXT("AUPCutSceneTriggerBossFirst : Can't Find UPGameInstance"));
		return;
	}
}

void AUPCutSceneTriggerBossFirst::PlayNextCutScene()
{
	if (UPGameInstance->bIsBossFirstMeet)
	{
		Super::PlayNextCutScene();
	}
	else if(bIsTriggerFirst)
	{
		bIsTriggerFirst = false;
		CameraMoveEventArray.Last().CutSceneEvent->FinishEvent();
	}
}
