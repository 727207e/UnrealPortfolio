// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BossManager.generated.h"

UCLASS()
class UNREALPORTFOLIO_API ABossManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABossManager();

	void GenBoss();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<AActor> GenPosition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ACharacter> BossBody;
	ACharacter* Boss;
};