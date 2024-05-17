// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Interface/WeaponControlInterface.h"
#include "GA_EquipWeapon.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPORTFOLIO_API UGA_EquipWeapon : public UGameplayAbility
{
	GENERATED_BODY()
	
protected:
	const int32 DEFAULT_WEAPON_ID = 0;
	
protected:
	UPROPERTY(EditAnywhere ,Category = GAS)
	int32 EquipWeaponId;
	UPROPERTY(EditAnywhere , Category = GAS)
	TSubclassOf<class UGameplayEffect> WeaponEffect;

	IWeaponControlInterface* WeaponControl;
	FActiveGameplayEffectHandle WeaponBuffActiveEffectHandle;
	FTimerHandle ComboTimerHandle;
protected:
	UGA_EquipWeapon();
	virtual auto ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
							 const FGameplayAbilityActivationInfo ActivationInfo,
							 const FGameplayEventData* TriggerEventData) -> void override;
	
	virtual auto CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
								   const FGameplayAbilityActivationInfo ActivationInfo,
								   bool bReplicateCancelAbility) -> void override;

	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

	void UnequipWeapon();
	
};
