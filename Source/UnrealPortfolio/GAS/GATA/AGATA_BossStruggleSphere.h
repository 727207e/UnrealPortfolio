// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAS/GATA/GATA_SphereTrace.h"
#include "Interface/AttackReplaceDataInterface.h"
#include "AGATA_BossStruggleSphere.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPORTFOLIO_API AAGATA_BossStruggleSphere : public AGATA_SphereTrace, public IAttackReplaceDataInterface
{
	GENERATED_BODY()
	
public :
	AAGATA_BossStruggleSphere();

	virtual FORCEINLINE float GetAttackValue() override { return AttackValue; }
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult);

	UFUNCTION()
	virtual void SearchAllTarget();

protected :

	virtual void GetAttributeSetting() override;
	virtual void StartTargeting() override;
	virtual	void InitTrace() override;

	UPROPERTY(EditAnywhere)
	float AttackValue;
	UPROPERTY(EditAnywhere)
	float SphereScaleValue;
};
