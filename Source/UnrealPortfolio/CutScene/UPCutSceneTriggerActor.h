// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TimeLineComponent.h"
#include "UPCutSceneTriggerActor.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnCutSceneEnd);

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
	TObjectPtr<AActor> DestinationCameraTrans;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<AActor> StartCameraTrans;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class AUPCutSceneEvent> CutSceneEvent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCurveFloat* CurveData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float PlayTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float StayTime;
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
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult);
	UFUNCTION(NetMulticast, Unreliable)
	void Multi_StartCutScene();
	UFUNCTION()
	virtual void PlayNextCutScene();

	FOnCutSceneEnd OnCutSceneEnd;

	UPROPERTY(EditAnywhere)
	bool bIsShareView;

protected :
	bool bIsTriggerFirst;

private :

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