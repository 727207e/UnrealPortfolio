// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAS/GATA/GATA_Trace.h"
#include "GATA_SquareTrace.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSquareOverlapDelegate, const FGameplayAbilityTargetDataHandle&, TargetDataHandle);

/**
 * 
 */
UCLASS()
class UNREALPORTFOLIO_API AGATA_SquareTrace : public AGATA_Trace
{
	GENERATED_BODY()
	
public :
	AGATA_SquareTrace();

public :
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UBoxComponent> Box;

	UPROPERTY()
	TObjectPtr<class AGameplaySkillEventDataRequest> CurrentData;

	UPROPERTY(BlueprintAssignable)
	FSquareOverlapDelegate OnTargetDetect;
public :
	virtual void ConfirmTargetingAndContinue() override;
	virtual void Destroyed() override;
	
	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult);


private :
	void InitSquareTrace();
};
