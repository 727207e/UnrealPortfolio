// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/UPCharacter.h"
#include "AbilitySystemInterface.h"
#include "Interface/AbilitySystemGetInterface.h"
#include "UPBattleBaseCharacter.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPORTFOLIO_API AUPBattleBaseCharacter : public AUPCharacter, public IAbilitySystemInterface, public IAbilitySystemGetInterface
{
	GENERATED_BODY()
	
public :
	AUPBattleBaseCharacter();
	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:
	virtual void PostInitializeComponents() override;

public :
	virtual void SetDead() override;
	
	UPROPERTY()
	TObjectPtr<class UAbilitySystemComponent> ASC;

//Battle Animation
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TObjectPtr<class UAnimMontage> ComboActionMontage;

//GAS
protected:

};
