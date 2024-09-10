// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAS/GATA/GATA_BaseRangeAttackTrace.h"
#include "GATA_RangeEnemeyFire.generated.h"

class UNiagaraSystem;
/**
 * 
 */
UCLASS()
class UNREALPORTFOLIO_API AGATA_RangeEnemeyFire : public AGATA_BaseRangeAttackTrace
{
	GENERATED_BODY()
	
public :
	AGATA_RangeEnemeyFire();

	void SetProjectileSpeed(float speed);

public :
	bool bIsSettingInSocket = true;

protected :
	virtual void Destroyed() override;
	virtual void BeginPlay() override;

	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult) override;
	virtual void SettingProjectile() override;
};
