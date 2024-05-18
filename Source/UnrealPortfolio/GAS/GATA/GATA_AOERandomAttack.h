// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAS/GATA/GATA_SkillTrace.h"
#include "GATA_AOERandomAttack.generated.h"

class UNiagaraSystem;
/**
 * 
 */
UCLASS()
class UNREALPORTFOLIO_API AGATA_AOERandomAttack : public AGATA_SkillTrace
{
	GENERATED_BODY()
	
public :
	AGATA_AOERandomAttack();
	virtual void ConfirmTargetingAndContinue() override;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UNiagaraSystem> AOEVisual;
	UPROPERTY(EditAnywhere)
	TObjectPtr<UNiagaraSystem> ExploreVisual;

	UFUNCTION()
	void OnAOEAttackArea(FGameplayTag TargetTag);

	UPROPERTY(ReplicatedUsing = OnRep_RandomTargetLocations)
	mutable TArray<FVector> RandomTargetLocations;
	mutable FDelegateHandle AttackEffectHandle;

	UPROPERTY(Replicated)
	TObjectPtr<AActor> ReplcateSourceActorValue;

	UFUNCTION()
	void OnRep_RandomTargetLocations();

	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;

protected:
	virtual FGameplayAbilityTargetDataHandle MakeTargetData() const override;
	virtual TArray<FVector> GetRandomRadiusPosition() const;
	virtual void AttackArea() const;

	void DeactiveTA() const;

private :
	float SearchingRadius = 0;
	float NiagaraSize = 0;
	float AttackTimeDelay = 0;
	float TargetTraceAreaOffset = 0;
	FGameplayTag ThisTargetTag;

	void AddAttackEvent();
};
