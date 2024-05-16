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

	virtual void BeginPlay() override;
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult);
	virtual void DrawDecal() override;

	virtual FORCEINLINE float GetAttackValue() override { return AttackValue; }
	virtual FORCEINLINE int32 GetAttackCount() override { return AttackCount; }
protected :
	virtual void GetAttributeSetting() override;
	virtual void StartTargeting() override;

	UFUNCTION()
	void SearchAllTarget();

	UPROPERTY(EditAnywhere)
	float AttackValue;
	UPROPERTY(EditAnywhere)
	int32 AttackCount;

	UFUNCTION()
	void SpawnGC(FTransform TargetTransform);
};
