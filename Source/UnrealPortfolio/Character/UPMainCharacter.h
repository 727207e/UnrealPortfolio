// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/UPCharacter.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "Interface/AbilitySystemGetInterface.h"
#include "Interface/UPPossessCharacterInterface.h"
#include "UPMainCharacter.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPORTFOLIO_API AUPMainCharacter : public AUPCharacter, public IAbilitySystemGetInterface, public IUPPossessCharacterInterface
{
	GENERATED_BODY()
	
public :
	AUPMainCharacter();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	virtual void PossessedBy(AController* NewController) override;

	virtual	void OnAttackStart() override;
	virtual void OnSkillStart(int32 Index) override;
	virtual void OnSkillRelease(int32 Index) override;
	virtual void OnConsumableStart(int32 Index) override;
	virtual void OnAvoidStart() override;
	virtual void OnMenuStart() override;
	virtual void OnInventoryStart() override;

	virtual void OnInputStart() override;
	virtual void OnSetDestinationTriggered() override;
	virtual void OnSetDestinationReleased() override;
	
	/** Time Threshold to know if it was a short press */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	float ShortPressThreshold;

	/** FX Class that we will spawn when clicking */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<class UNiagaraSystem> FXCursor;

protected :
	UPROPERTY(EditAnywhere, Category = GAS)
	TObjectPtr<class UAbilitySystemComponent> ASC;

	UPROPERTY(EditAnywhere, Category = GAS)
	TArray<TSubclassOf<class UGameplayAbility>> StartAbilities;
	
	UPROPERTY(EditAnywhere, Category = GAS)
	TMap<int32, TSubclassOf<class UGameplayAbility>> StartInputAbilities;

private :
	void SetupGasInput(AController* NewController);

private :
	//Movement
	float FollowTime; // For how long it has been pressed
	FVector CachedDestination;
};
