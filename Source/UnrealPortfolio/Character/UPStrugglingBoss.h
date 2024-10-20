// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "UPBattleBaseCharacter.h"
#include "UPStrugglingBoss.generated.h"

UCLASS()
class UNREALPORTFOLIO_API AUPStrugglingBoss : public AUPBattleBaseCharacter
{
	GENERATED_BODY()

public:
	AUPStrugglingBoss();

	UPROPERTY(EditAnywhere)
	TArray<int32> StrugglePatern;

	void StartPatern();
	void PlayNextPatern();

protected :
	virtual void Hit(FVector TargetLocation, TObjectPtr<class AGameplayEventDataRequest> ActionData) override;

	void PlayPatern();
private :
	float StartDelay = 0;
	float NextPlayDelay = 0;
	int PaternIndex = 0;
};