// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BossManager.generated.h"

USTRUCT(BlueprintType)
struct FBossHealthEvent
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class AUPCutSceneTriggerActor> CutSceneTrigger;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BossTriggerHp = 0;
};

UCLASS()
class UNREALPORTFOLIO_API ABossManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABossManager();

	virtual void PreInitializeComponents() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<AActor> GenPosition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ACharacter> BossBody;
	class AUPBossCharacter* Boss;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class AUPCutSceneTriggerActor> CutSceneTrigger; 

	UPROPERTY(EditAnywhere)
	TSubclassOf<ACharacter> StruggleBossDummy;

	UPROPERTY(EditAnywhere)
	float Radius = 4000.f;

	UPROPERTY(EditAnywhere)
	float ZOffset = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FBossHealthEvent> BossTriggers;

	UPROPERTY(EditAnywhere)
	float BossPhaseNumber = 1;
	UPROPERTY(EditAnywhere)
	float BossStartingHP = -1;

	uint8 bIsBossDie = 0;

	UPROPERTY(EditAnywhere)
	bool bIsSpawnImmediately = false;

public :
	void GenBoss();
	virtual void BeginPlay() override;

	void StartStruggling();
	FTransform GetRandomAroundTransform();

	UFUNCTION()
	void BossHPTriggerCheck();

	void BossDestroy();

private :
	void SpawnActorsAroundCenter(const FVector& Center);
	TArray<FVector> CalculatePositionsAroundCenter(const FVector& Center);

	TArray<AActor*> AroundActors;
};