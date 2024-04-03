// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/UPCharacter.h"
#include "AbilitySystemInterface.h"
#include "Interface/AbilitySystemGetInterface.h"
#include "UPEnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPORTFOLIO_API AUPEnemyCharacter : public AUPCharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public :
	AUPEnemyCharacter();

	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:
	virtual void PostInitializeComponents() override;

public :
	virtual void SetDead() override;
	
	UPROPERTY()
	TObjectPtr<class UAbilitySystemComponent> ASC;
};
