// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_GASTagsEdit.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPORTFOLIO_API UAnimNotify_GASTagsEdit : public UAnimNotify
{
	GENERATED_BODY()

public :
	UPROPERTY(EditAnywhere)
	TArray<FName> TagList;

	UPROPERTY(EditAnywhere)
	bool bIsAddTag = true;

protected:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
};