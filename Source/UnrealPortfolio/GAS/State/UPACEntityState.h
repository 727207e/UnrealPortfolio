// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interface/AbilitySystemGetInterface.h"
#include "GAS/Attribute/EntityAttributeSet.h"
#include "UPACEntityState.generated.h"


UCLASS(Blueprintable)
class UNREALPORTFOLIO_API UUPACEntityState : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UUPACEntityState();

	virtual void InitEntityState(AActor* Owner);
	virtual void PostInitialize();
public :
	UPROPERTY(EditAnywhere, Category = GAS)
	TObjectPtr<class UAbilitySystemComponent> ASC;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UEntityAttributeSet> AttributeSetType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class UEntityAttributeSet> AttributeSet;
};