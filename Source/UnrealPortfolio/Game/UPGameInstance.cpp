// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/UPGameInstance.h"
#include "Game/BossManager.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/LevelStreaming.h"
#include "Engine/World.h"

UUPGameInstance::UUPGameInstance()
{
}

ABossManager* UUPGameInstance::GetBossManager() const
{
    if (nullptr == BossManager)
    {
        UE_LOG(LogTemp, Error, TEXT("UPGameInstance : Can't Find BossManager"));
    }
    return BossManager;
}

void UUPGameInstance::SetBossManager(ABossManager* TargetBossManager)
{
    BossManager = TargetBossManager;
}