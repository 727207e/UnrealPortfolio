// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/GA/Item/GA_EquipWeapon.h"

#include "AbilitySystemComponent.h"
#include "Interface/WeaponControlInterface.h"
#include "Item/StaticMeshWeaponComponent.h"
#include "Tag/GameplayTags.h"

UGA_EquipWeapon::UGA_EquipWeapon(): EquipWeaponId(DEFAULT_WEAPON_ID), WeaponControl(nullptr)
{
	AbilityTags.AddTag(TAG_WEAPON);
	ActivationOwnedTags.AddTag(TAG_CHARACTER_STATE_EQUIP_WEAPON);
}

void UGA_EquipWeapon::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                      const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                      const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	WeaponControl = Cast<IWeaponControlInterface>(ActorInfo->AvatarActor);
	if(WeaponControl)
	{
		const UStaticMeshWeaponComponent* WeaponComponent = WeaponControl->GetEquipWeapon();
		EquipWeaponId = WeaponComponent->GetWeaponId();
		const FGameplayEffectSpecHandle EffectSpecHandle = MakeOutgoingGameplayEffectSpec(WeaponEffect, WeaponComponent->WeaponLevel);
		if (EffectSpecHandle.IsValid())
		{
			WeaponBuffActiveEffectHandle = ApplyGameplayEffectSpecToOwner(CurrentSpecHandle,CurrentActorInfo,CurrentActivationInfo,EffectSpecHandle);
		}
	}
	else
	{
		UE_LOG(LogTemp,Error,TEXT("GA_EquipWeapon Not found WeaponControlInterface"));
	}
}

void UGA_EquipWeapon::CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility)
{
	UnequipWeapon();
	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);
	
}

void UGA_EquipWeapon::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	UnequipWeapon();
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UGA_EquipWeapon::UnequipWeapon()
{
	UStaticMeshWeaponComponent* EquipTargetWeapon = WeaponControl->GetEquipWeapon();
	EquipTargetWeapon->Hidden();
	GetAbilitySystemComponentFromActorInfo()->RemoveActiveGameplayEffect(WeaponBuffActiveEffectHandle);

}
