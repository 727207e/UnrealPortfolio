// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AbilitySystemComponent.h"
#include "GameplayEventDataRequest.generated.h"

UCLASS()
class UNREALPORTFOLIO_API AGameplayEventDataRequest : public AActor
{
	GENERATED_BODY()
public:
	int32 ActionId;
	FName ActionRowName;
	FGameplayTag ActionGC;
};
