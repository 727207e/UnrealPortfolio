// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interface/AbilitySystemGetInterface.h"
#include "Data/DataAttributeSet/EntityAttributeSet.h"
#include "UPACEntityState.generated.h"


UCLASS(Blueprintable)
class UNREALPORTFOLIO_API UUPACEntityState : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UUPACEntityState();

	virtual void BeginPlay() override;

public :
	UPROPERTY(EditAnywhere, Category = GAS)
	TObjectPtr<class UAbilitySystemComponent> ASC;

	///Test Method . Plz Delete This!
	void TestMethod();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UEntityAttributeSet> AttributeSet;
};