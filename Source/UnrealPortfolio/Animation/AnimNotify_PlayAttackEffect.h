// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AbilitySystemComponent.h"
#include "AnimNotify_PlayAttackEffect.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPORTFOLIO_API UAnimNotify_PlayAttackEffect : public UAnimNotify
{
	GENERATED_BODY()

protected:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

protected:
	UPROPERTY(EditAnywhere)
	FGameplayTag TriggerTag;
};
