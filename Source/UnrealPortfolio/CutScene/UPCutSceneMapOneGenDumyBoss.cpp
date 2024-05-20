// Fill out your copyright notice in the Description page of Project Settings.


#include "CutScene/UPCutSceneMapOneGenDumyBoss.h"
#include "GameFramework/Character.h"
#include "Game/BossManager.h"

void AUPCutSceneMapOneGenDumyBoss::StartEvent()
{
	if (!HasAuthority())
	{
		return;
	}
	Super::StartEvent();

	DumyBoss = GetWorld()->SpawnActor<ACharacter>(DumyBossType, GenPosition->GetActorLocation(), GenPosition->GetActorRotation());
}

void AUPCutSceneMapOneGenDumyBoss::FinishEvent()
{
	if (!HasAuthority())
	{
		return;
	}
	Super::FinishEvent();

	DumyBoss->Destroy();

	FTimerHandle RealBossGenTimeHandle;
	GetWorld()->GetTimerManager().SetTimer(RealBossGenTimeHandle, FTimerDelegate::CreateLambda([&]
		{
			BossManager->GenBoss();
		}), 2.0f, false);
}
