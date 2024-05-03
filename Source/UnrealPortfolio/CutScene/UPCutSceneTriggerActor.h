// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UPCutSceneTriggerActor.generated.h"

UCLASS()
class UNREALPORTFOLIO_API AUPCutSceneTriggerActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AUPCutSceneTriggerActor();

	UPROPERTY()
	class UBoxComponent* BoxRoot;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<APawn> TargetCameraTrans;

public :
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult);

private :
	bool bIsTriggerFirst;
	void CameraMoveTimer();
	FTimerHandle CameraMoveTimerHandle;
};
