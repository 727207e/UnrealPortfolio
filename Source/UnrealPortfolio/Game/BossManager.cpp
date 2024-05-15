// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/BossManager.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "CutScene/UPCutSceneTriggerActor.h"

// Sets default values
ABossManager::ABossManager()
{
	
}

void ABossManager::GenBoss()
{
	Boss = GetWorld()->SpawnActor<ACharacter>(BossBody, GenPosition->GetActorLocation(), GenPosition->GetActorRotation());

}

void ABossManager::BeginPlay()
{
	if (CutSceneTrigger)
	{
		CutSceneTrigger->OnCutSceneEnd.AddUObject(this, &ABossManager::StartStruggling);
	}
}

void ABossManager::StartStruggling()
{	
	if (StruggleBossDummy)
	{
		ACharacter* struggle = Cast<ACharacter>(GetWorld()->SpawnActor(StruggleBossDummy));
		if (struggle)
		{
			struggle->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
		}
	}
}

