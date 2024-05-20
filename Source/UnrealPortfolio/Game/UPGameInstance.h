// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "UPGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPORTFOLIO_API UUPGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
    UUPGameInstance();

    UFUNCTION(BlueprintCallable, Category = "Manager")
    class ABossManager* GetBossManager() const;

    UFUNCTION(BlueprintCallable, Category = "Manager")
    void SetBossManager(class ABossManager* TargetBossManager);

    UPROPERTY()
    FString PlayerNickname;

private:
    UPROPERTY()
    class ABossManager* BossManager;
};