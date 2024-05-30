// Fill out your copyright notice in the Description page of Project Settings.


#include "CutScene/UPCutSceneMapOneGenDumyBoss.h"
#include "GameFramework/Character.h"
#include "Game/UPGameInstance.h"
#include "Game/BossManager.h"

void AUPCutSceneMapOneGenDumyBoss::StartEvent()
{
	if (!HasAuthority())
	{
		return;
	}
	Super::StartEvent();

	DummyBoss = GetWorld()->SpawnActor<ACharacter>(DumyBossType, GenPosition->GetActorLocation(), GenPosition->GetActorRotation());
}

void AUPCutSceneMapOneGenDumyBoss::FinishEvent()
{
	if (!HasAuthority())
	{
		return;
	}
	Super::FinishEvent();

	UUPGameInstance* UPGameInstance = Cast<UUPGameInstance>(GetWorld()->GetGameInstance());
	if (nullptr == UPGameInstance)
	{
		UE_LOG(LogTemp, Error, TEXT("AUPCutSceneTriggerBossFirst : Can't Find UPGameInstance"));
		return;
	}
	UPGameInstance->bIsBossFirstMeet = false;

	if (nullptr != DummyBoss)
	{
		DummyBoss->Destroy();
	}

	FTimerHandle RealBossGenTimeHandle;
	GetWorld()->GetTimerManager().SetTimer(RealBossGenTimeHandle, FTimerDelegate::CreateLambda([&]
		{
			BossManager->GenBoss();
		}), 2.0f, false);
}
