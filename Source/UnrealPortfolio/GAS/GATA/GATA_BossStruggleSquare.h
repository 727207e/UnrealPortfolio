// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAS/GATA/GATA_SquareTrace.h"
#include "Interface/AttackReplaceDataInterface.h"
#include "GATA_BossStruggleSquare.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPORTFOLIO_API AGATA_BossStruggleSquare : public AGATA_SquareTrace, public IAttackReplaceDataInterface
{
	GENERATED_BODY()
	
public :
	AGATA_BossStruggleSquare();

	UPROPERTY(EditAnywhere)
	FVector BoxSizeValue;

	UPROPERTY(EditAnywhere)
	FVector BoxOffsetValue;

	UPROPERTY(EditAnywhere)
	float GCPoisionOffset;

	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult);
	virtual	void InitSquareTrace() override;

	virtual FORCEINLINE float GetAttackValue() override { return AttackValue; }

protected :
	virtual void GetAttributeSetting() override;
	virtual void StartTargetingN() override;

	UFUNCTION()
	void SearchAllTarget();

	UPROPERTY(EditAnywhere)
	float AttackValue;
	UPROPERTY(EditAnywhere)
	int32 AttackCount;
	UPROPERTY(EditAnywhere)
	int32 AttackOffset;

	UFUNCTION()
	void SpawnGC(FTransform TargetTransform);

private :
	TArray<TObjectPtr<class UBoxComponent>> Boxs;
};
