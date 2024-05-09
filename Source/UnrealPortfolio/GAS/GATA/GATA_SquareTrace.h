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

public :
	virtual void ConfirmTargetingAndContinue() override;
	virtual void Destroyed() override;

	virtual void BeginPlay() override;
	
	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult);


private :
	void InitSquareTrace();
};
