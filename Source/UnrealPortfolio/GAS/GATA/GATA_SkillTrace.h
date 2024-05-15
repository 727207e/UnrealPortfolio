// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTargetActor.h"
#include "GAS/GATA/GATA_Trace.h"
#include "GATA_SkillTrace.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSquareOverlapDelegate, const FGameplayAbilityTargetDataHandle&, TargetDataHandle);

/**
 * 
 */
UCLASS()
class UNREALPORTFOLIO_API AGATA_SkillTrace : public AGATA_Trace
{
	GENERATED_BODY()

public :
	AGATA_SkillTrace();

	UPROPERTY()
	TObjectPtr<class AGameplaySkillEventDataRequest> CurrentData;

	UPROPERTY(BlueprintAssignable)
	FSquareOverlapDelegate OnTargetDetect;

	UPROPERTY(EditAnywhere)
	bool bIsDrawDecal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class USceneComponent> RootSceneComponent;

public :
	virtual void ConfirmTargetingAndContinue() override;
	UFUNCTION()
	virtual void DrawDecal();
};