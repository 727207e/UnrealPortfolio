// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAS/AbilityTask/AbilityTask_Trace.h"
#include "GAS/GATA/GATA_Trace.h"
#include "GAS/Actor/GameplaySkillEventDataRequest.h"
#include "AbilityTask_SkillGen.generated.h"

UCLASS()
class UNREALPORTFOLIO_API UAbilityTask_SkillGen : public UAbilityTask_Trace
{
	GENERATED_BODY()
public:
	UAbilityTask_SkillGen();

	static UAbilityTask_SkillGen* CreateTaskWithData(UGameplayAbility* OwningAbility, TSubclassOf<AGATA_Trace> TargetActorClass, TObjectPtr<AGameplaySkillEventDataRequest> Data);

public :
	virtual void SpawnAndInitializeTargetActor() override;

	UPROPERTY(BlueprintAssignable)
	FTraceResultDelegate OnTargetDetect;
protected :
	UPROPERTY()
	TObjectPtr<AGameplaySkillEventDataRequest> CurrentData;

	UFUNCTION()
	void CallBackTargetDetect(const FGameplayAbilityTargetDataHandle& DataHandle);

};