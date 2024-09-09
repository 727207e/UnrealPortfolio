// Fill out your copyright notice in the Description page of Project Settings.

#include "CutScene/UPCutSceneEvent.h"
#include "Game/UPGameInstance.h"

// Sets default values
AUPCutSceneEvent::AUPCutSceneEvent()
{
}

void AUPCutSceneEvent::BeginPlay()
{
	Super::BeginPlay();

	UUPGameInstance* UPGameInstance = Cast<UUPGameInstance>(GetWorld()->GetGameInstance());
	if (nullptr == UPGameInstance)
	{
		UE_LOG(LogTemp, Error, TEXT("AUPCutSceneEvent : Can't Find UpGameInstance"));
		return;
	}

	BossManager = UPGameInstance->GetBossManager();
}

void AUPCutSceneEvent::StartEvent()
{
}

void AUPCutSceneEvent::FinishEvent()
{
}
