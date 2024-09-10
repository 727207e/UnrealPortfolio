// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "Interface/AbilitySystemGetInterface.h"
#include "UPPlayerState.generated.h"

class UUPMainCharacterAttributeSet;
class UAbilitySystemComponent;

/**
 * 
 */
UCLASS()
class UNREALPORTFOLIO_API AUPPlayerState : public APlayerState, public IAbilitySystemGetInterface
{
	GENERATED_BODY()
	
public:
	AUPPlayerState();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	class UEntityAttributeSet* GetMainCharacterAttributeSet() const;

protected:
	UPROPERTY(EditAnywhere, Category = GAS)
	TObjectPtr<UAbilitySystemComponent> ASC;
	UPROPERTY(EditAnywhere,Category = GAS)
	TObjectPtr<UUPMainCharacterAttributeSet> AttributeSet;
};
