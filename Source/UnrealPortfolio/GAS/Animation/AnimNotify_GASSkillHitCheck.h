// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "GameplayTagContainer.h"
#include "GAS/GATA/GATA_Trace.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_GASSkillHitCheck.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPORTFOLIO_API UAnimNotify_GASSkillHitCheck : public UAnimNotify
{
	GENERATED_BODY()
	
protected:
	virtual FString GetNotifyName_Implementation() const override;
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
protected:
	UPROPERTY(EditAnywhere)
	FGameplayTag TriggerTag;
	UPROPERTY(EditAnywhere)
	FName TargetAttributeSetName;
	UPROPERTY(EditAnywhere)
	FName TargetGenName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	TSubclassOf<AGATA_Trace> TargetTA;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	FGameplayTag TargetGC;
};