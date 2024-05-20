// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayMultiCueEventData.generated.h"

UCLASS(Blueprintable)
class UNREALPORTFOLIO_API AGameplayMultiCueEventData : public AActor
{
	GENERATED_BODY()
	
public :
	AGameplayMultiCueEventData();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_SpawnLocations)
	TArray<FVector> SpawnLocations;

	UFUNCTION()
	void OnRep_SpawnLocations();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
