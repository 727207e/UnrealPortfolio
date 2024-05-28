// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilityTask_Trace.h"
#include "GAS/GATA/GATA_LivingPlayerTracker.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "AbilityTask_LivingPlayerTracker.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPORTFOLIO_API UAbilityTask_LivingPlayerTracker : public UAbilityTask
{
public:
	GENERATED_BODY()
	UAbilityTask_LivingPlayerTracker();
	static UAbilityTask_LivingPlayerTracker* CreateTask(UGameplayAbility* OwningAbility, TSubclassOf<AGATA_LivingPlayerTracker> TargetActorClass);

	virtual void Activate() override;
	virtual void OnDestroy(bool AbilityEnded) override;
	virtual void SpawnAndInitializeTargetActor();
	void FinalizeTargetActor();
public:
	UPROPERTY(BlueprintAssignable)
	FTraceResultDelegate OnComplete;
protected:
	UPROPERTY()
	TObjectPtr<class AGATA_LivingPlayerTracker> SpawnedTargetActor;
	void OnTargetDataReadyCallback(const FGameplayAbilityTargetDataHandle& DataHandle);
	UPROPERTY()
	TSubclassOf<class AGATA_Trace> TargetActorClass;
    
};
