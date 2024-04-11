// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "GAS/GATA/GATA_Trace.h"
#include "AbilityTask_Trace.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTraceResultDelegate, const FGameplayAbilityTargetDataHandle&, TargetDataHandle);


UCLASS()
class UNREALPORTFOLIO_API UAbilityTask_Trace : public UAbilityTask
{
	GENERATED_BODY()
public:
	UAbilityTask_Trace();
    
	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (DisplayName = "WaitForTrace", HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))

	//static UAT_Trace* CreateTask(UGameplayAbility* OwningAbility, TSubclassOf<class UAT_Trace> TargetActorClass);
	static UAbilityTask_Trace* CreateTask(UGameplayAbility* OwningAbility, TSubclassOf<AGATA_Trace> TargetActorClass);

	virtual void Activate() override;
	virtual void OnDestroy(bool AbilityEnded) override;
    
	void SpawnAndInitializeTargetActor();
	void FinalizeTargetActor();
    
protected:
	void OnTargetDataReadyCallback(const FGameplayAbilityTargetDataHandle& DataHandle);
    
public:
	UPROPERTY(BlueprintAssignable)
	FTraceResultDelegate OnComplete;
    
protected:
	UPROPERTY()
	TSubclassOf<class AGATA_Trace> TargetActorClass;

	UPROPERTY()
	TObjectPtr<class AGATA_Trace> SpawnedTargetActor;

};
