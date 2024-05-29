// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UPMoveNextLevelActor.generated.h"

UCLASS()
class UNREALPORTFOLIO_API AUPMoveNextLevelActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AUPMoveNextLevelActor();

public :
	UPROPERTY()
	class UBoxComponent* BoxRoot;

	UPROPERTY(EditAnywhere)
	FString TargetNextLevel;

	UPROPERTY()
	TObjectPtr<class ABossManager> TargetBossManager;

public :
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult);

private :
	void MoveNextLevel();
};
