// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TimeLineComponent.h"
#include "UPCutSceneTriggerActor.generated.h"

UENUM()
enum class EStartType : uint8
{
	StartCamera,
	StartArrayValue
};

USTRUCT(BlueprintType)
struct FCameraMoveEvent
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EStartType StartType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<APawn> DestinationCameraTrans;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<APawn> StartCameraTrans;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCurveFloat* CurveData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MoveLimitTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 StayLimitTime;
};

UCLASS()
class UNREALPORTFOLIO_API AUPCutSceneTriggerActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AUPCutSceneTriggerActor();

	UPROPERTY()
	class UBoxComponent* BoxRoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FCameraMoveEvent> CameraMoveEventArray;

public :
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult);

private :
	void SettingTimer();
	void CutSceneFinish();

	bool bIsTriggerFirst;
	void CameraMoveTimer();
	FTimerHandle CameraMoveTimerHandle;
	FCameraMoveEvent CameraMoveEvent;

	class AUPMainCharacter* MyCharacter;
	class UCameraComponent* MainCamera;
	class UCurveFloat* TargetCurveFloat;
	FTransform StartTransform;
	FTransform DestinationTransform;

	int32 IndexCount;
	float CurTime;
};