// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAS/GATA/GATA_SkillTrace.h"
#include "GATA_SquareTrace.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPORTFOLIO_API AGATA_SquareTrace : public AGATA_SkillTrace
{
	GENERATED_BODY()
	
public :
	AGATA_SquareTrace();

public :
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UBoxComponent> Box;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class UDecalComponent> SquareDecal;

public :
	virtual void ConfirmTargetingAndContinue() override;
	virtual void Destroyed() override;
	virtual void BeginPlay() override;
	
	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult);
	
	virtual void DrawDecal() override;

protected :
	virtual void GetAttributeSetting();

	int32 BoxSizeX;
	int32 BoxSizeY;
	int32 BoxSizeZ;

	int32 DecalDelayTime = 0;
	int32 DestroyTATime = 0;

private :
	void InitSquareTrace();
	void StartTargeting();

};
