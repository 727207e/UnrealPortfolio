// Fill out your copyright notice in the Description page of Project Settings.


#include "CutScene/UPCutSceneBossRun.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Game/BossManager.h"

void AUPCutSceneBossRun::StartEvent()
{
	if (!HasAuthority())
	{
		return;
	}

	if (BossManager->Boss != nullptr)
	{
		BossManager->Boss->Destroy();
		BossManager->Boss = nullptr;
	}
	
	DumyBoss = GetWorld()->SpawnActor<ACharacter>(DumyBossType, GenPosition->GetActorLocation(), GenPosition->GetActorRotation());
	if (DumyBoss)
	{
		DumyBoss->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
	}
}

void AUPCutSceneBossRun::FinishEvent()
{
	if (!HasAuthority())
	{
		return;
	}

	if (IsValid(DumyBoss) && !DumyBoss->HasAnyFlags(RF_BeginDestroyed)) 
	{
		GetWorld()->GetTimerManager().ClearAllTimersForObject(DumyBoss.Get());

		DumyBoss->Destroy();
		DumyBoss = nullptr;
	}
}
