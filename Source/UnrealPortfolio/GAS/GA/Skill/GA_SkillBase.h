// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Interface/AttackableCharacterInterface.h"
#include "Interface/CharacterMovementInterface.h"
#include "GA_SkillBase.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnSkillEndDelegate);

/**
 * 
 */
UCLASS()
class UNREALPORTFOLIO_API UGA_SkillBase : public UGameplayAbility
{
	GENERATED_BODY()

protected:
	IAttackableCharacterInterface*  AttackableCharacter;
	ICharacterMovementInterface* MovementCharacter;

	UPROPERTY(EditAnywhere)
	FName TargetMontageSectionName = NAME_None;

public:
	UPROPERTY(EditAnywhere)
	UAnimMontage* TargetMontage;

	FOnSkillEndDelegate OnEndSkillDelegate;

protected:
	virtual auto ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
							 const FGameplayAbilityActivationInfo ActivationInfo,
							 const FGameplayEventData* TriggerEventData) -> void override;
	

	/** Destroys instanced-per-execution abilities. Instance-per-actor abilities should 'reset'. Any active ability state tasks receive the 'OnAbilityStateInterrupted' event. Non instance abilities - what can we do? */
	virtual auto CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
							   const FGameplayAbilityActivationInfo ActivationInfo,
							   bool bReplicateCancelAbility) -> void override;

	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

	virtual void InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) override;
	
	UFUNCTION()
	virtual void OnCompleteCallback();
	UFUNCTION()
	virtual void OnInterruptedCallback();
	
	float AttackSpeed = 1.0f;
};

