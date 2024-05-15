// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NiagaraSystem.h"
#include "GAS/GATA/GATA_Trace.h"
#include "GATA_BaseRangeAttackTrace.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPORTFOLIO_API AGATA_BaseRangeAttackTrace : public AGATA_Trace
{
	GENERATED_BODY()
public:

	AGATA_BaseRangeAttackTrace();
	
protected:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GAS", meta = (BoneName = "true"))
	FName SocketName;
	
	UPROPERTY(EditAnywhere , Category = GAS)
	TObjectPtr<UNiagaraSystem> MuzzleFX;

	UPROPERTY(EditAnywhere, Category = GAS)
	TObjectPtr<UNiagaraSystem> ProjectileFX;

	UPROPERTY(EditAnywhere ,Category = GAS)
	TObjectPtr<UNiagaraSystem> HitFX;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UProjectileMovementComponent> ProjectTileMovement;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class USphereComponent> Sphere;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UNiagaraComponent> MuzzleComponent;
	
protected :
	virtual void ConfirmTargetingAndContinue() override;
	virtual void Destroyed() override;
	
	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult);

	virtual void SettingProjectile();
	virtual void AutoDestroy();
};
