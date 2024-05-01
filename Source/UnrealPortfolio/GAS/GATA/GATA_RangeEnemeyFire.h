// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTargetActor.h"
#include "GATA_RangeEnemeyFire.generated.h"

class UNiagaraSystem;
/**
 * 
 */
UCLASS()
class UNREALPORTFOLIO_API AGATA_RangeEnemeyFire : public AGameplayAbilityTargetActor
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
	TObjectPtr<class USphereComponent> Sphere;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UNiagaraComponent> MuzzleComponent;

public :
	virtual void BeginPlay() override;
};
