// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "GameplayTagContainer.h"
#include "GAS/GATA/GATA_Trace.h"
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
	FGameplayTag TriggerTag;
	UPROPERTY(EditAnywhere, Category = Anim)
	float AttackLevel;
	UPROPERTY(EditAnywhere, Category = Data)
	int32 ActionId;
	UPROPERTY(EditAnywhere,Category = Data)
	FName ActionRowName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	TSubclassOf<AGATA_Trace> TargetTA;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	FGameplayTag TargetGC;
};
