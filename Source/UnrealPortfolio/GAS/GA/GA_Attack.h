// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Data/UPComboActionData.h"
#include "Interface/AttackableCharacterInterface.h"
#include "Interface/CharacterMovementInterface.h"
#include "Data/UPComboActionData.h"
#include "GA_Attack.generated.h"
/**
 * 
 */
UCLASS()
class UNREALPORTFOLIO_API UGA_Attack : public UGameplayAbility
{
	GENERATED_BODY()
	virtual auto ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
							 const FGameplayAbilityActivationInfo ActivationInfo,
							 const FGameplayEventData* TriggerEventData) -> void override;
	

	/** Destroys instanced-per-execution abilities. Instance-per-actor abilities should 'reset'. Any active ability state tasks receive the 'OnAbilityStateInterrupted' event. Non instance abilities - what can we do? */
	virtual auto CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
							   const FGameplayAbilityActivationInfo ActivationInfo,
							   bool bReplicateCancelAbility) -> void override;

	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

	virtual void InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) override;

	IAttackableCharacterInterface*  AttackableCharacter;
	ICharacterMovementInterface* MovementCharacter;
	FName GetNextSection();
protected:
	//FMontageWaitSimpleDelegate
	UFUNCTION()
	void OnCompleteCallback();
	UFUNCTION()
	void OnInterruptedCallback();
	UFUNCTION()
	void StartComboTimer();
	UFUNCTION()
	void CheckComboInput();
	
	protected:
    	UPROPERTY()
    	TObjectPtr<class UUPComboActionData> CurrentComboData;
    
    	uint8 CurrentCombo = 0;
    	FTimerHandle ComboTimerHandle;
    	bool HasNextComboInput = false;
};
