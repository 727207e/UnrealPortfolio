// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/BossManager.h"
#include "GameFramework/Character.h"

// Sets default values
ABossManager::ABossManager()
{

}

void ABossManager::GenBoss()
{
	Boss = GetWorld()->SpawnActor<ACharacter>(BossBody, GenPosition->GetActorLocation(), GenPosition->GetActorRotation());

}

