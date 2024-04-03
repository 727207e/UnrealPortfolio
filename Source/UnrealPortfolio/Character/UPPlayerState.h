// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "Interface/AbilitySystemGetInterface.h"
#include "UPPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPORTFOLIO_API AUPPlayerState : public APlayerState, public IAbilitySystemGetInterface
{
	GENERATED_BODY()
	
public:
	AUPPlayerState();

	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:
	UPROPERTY(EditAnywhere, Category = GAS)
	TObjectPtr<class UAbilitySystemComponent> ASC;
};
