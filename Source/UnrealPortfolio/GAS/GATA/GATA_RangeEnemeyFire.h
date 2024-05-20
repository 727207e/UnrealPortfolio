// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAS/GATA/GATA_SkillTrace.h"
#include "GATA_RangeEnemeyFire.generated.h"

class UNiagaraSystem;
/**
 * 
 */
UCLASS()
class UNREALPORTFOLIO_API AGATA_RangeEnemeyFire : public AGATA_SkillTrace
{
	GENERATED_BODY()
	
public :
	AGATA_RangeEnemeyFire();

public :
	UPROPERTY(EditAnywhere)
	TObjectPtr<UNiagaraSystem> MuzzleFX;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UNiagaraSystem> ProjectileFX;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UNiagaraSystem> HitFX;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UProjectileMovementComponent> ProjectTileMovement;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UCapsuleComponent> Capsule;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UNiagaraComponent> MuzzleComponent;

	FName SocketName;
	bool bIsSettingInSocket = true;

public :
	virtual void ConfirmTargetingAndContinue() override;
	virtual void Destroyed() override;
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult);
	void SetProjectileSpeed(float speed);

protected :
	void AutoDestroy();

private :
	void SettingProjectile();
};
