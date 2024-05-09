// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AbilitySystemComponent.h"
#include "GameplaySkillEventDataRequest.generated.h"

UCLASS()
class UNREALPORTFOLIO_API AGameplaySkillEventDataRequest : public AActor
{
	GENERATED_BODY()
public:

	FGameplayTag ActionGC;
	FName TargetGenName;
	const class UUPBossSkillAttributeSet* TargetAttributeSet;
};
