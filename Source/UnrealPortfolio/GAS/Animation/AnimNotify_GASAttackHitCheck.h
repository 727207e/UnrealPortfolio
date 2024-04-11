// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "GameplayTagContainer.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_GASAttackHitCheck.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPORTFOLIO_API UAnimNotify_GASAttackHitCheck : public UAnimNotify
{
	GENERATED_BODY()
	
protected:
	virtual FString GetNotifyName_Implementation() const override;
	UAbilitySystemComponent* GetAbilitySystemComponent(AActor* Actor);
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
protected:
	UPROPERTY(EditAnywhere)
	FGameplayTag TriggetTag;
	
};
