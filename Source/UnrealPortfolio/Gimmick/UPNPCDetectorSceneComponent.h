// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "UPNPCDetectorSceneComponent.generated.h"

class IUPUINpcInterface;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALPORTFOLIO_API UUPNPCDetectorSceneComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UUPNPCDetectorSceneComponent();
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UBoxComponent> BoxComp;
public:
	UFUNCTION(BlueprintCallable)
	void Action() const;
private:
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult);
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	IUPUINpcInterface*  UINPC;
public:

public:
	UFUNCTION()
	void SetParent(USceneComponent* InParent);
	
	UPROPERTY(EditAnywhere)
	float SizeX;
	UPROPERTY(EditAnywhere)
	float SizeY;
	UPROPERTY(EditAnywhere)
	float SizeZ;
	
};
