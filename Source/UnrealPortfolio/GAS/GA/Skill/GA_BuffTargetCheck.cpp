// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/GA/Skill/GA_BuffTargetCheck.h"

#include "Character/UPPlayerState.h"
#include "Interface/HUDControllerInterface.h"

class AUPPlayerState;

void UGA_BuffTargetCheck::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                          const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                          const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	const AUPPlayerState* PlayerState = Cast<AUPPlayerState>(CurrentActorInfo->OwnerActor);
	if(IHUDControllerInterface* HudOwner = Cast<IHUDControllerInterface>(PlayerState->GetPlayerController()))
	{
		const TObjectPtr<UUPMainHudWidget> PlayerHud = HudOwner->GetHudWidget();
		if(PlayerHud)
		{
			TTuple<bool, TObjectPtr<USlotViewWidget>> MyTuple =  PlayerHud->GetLastBuffViewWidget(TargetSkillAbilityIndex);
			bool bUsedBuff = MyTuple.Get<0>();
			BuffSlot = MyTuple.Get<1>();
			if(bUsedBuff == false)
			{
				ApplyBuff();
			}
			else
			{
				GetActorInfo().AbilitySystemComponent->RemoveActiveGameplayEffectBySourceEffect(AttackDamageEffect,
					GetActorInfo().AbilitySystemComponent.Get());
				ApplyBuff();
			}
		}
	}
	
}

void UGA_BuffTargetCheck::CancelAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateCancelAbility)
{
	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);
}

void UGA_BuffTargetCheck::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UGA_BuffTargetCheck::OnBuffEnd()
{
	BuffSlot->BuffId = -1;
	BuffSlot->SetVisibility(ESlateVisibility::Hidden);

	bool bReplicatedEndAbility = true;
	bool bWasCancelled = false;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicatedEndAbility, bWasCancelled);
}

void UGA_BuffTargetCheck::ApplyBuff()
{
	BuffSlot->OnClickedTargetInputActionKey(10);
	BuffSlot->SetVisibility(ESlateVisibility::Visible);
	BuffSlot->CooldownFinishDelegate.AddDynamic(this,&UGA_BuffTargetCheck::OnBuffEnd);
	const FGameplayEffectSpecHandle EffectSpecHandle = MakeOutgoingGameplayEffectSpec(AttackDamageEffect);
	if (EffectSpecHandle.IsValid())
	{
		//ApplyGameplayEffectSpecToTarget(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, EffectSpecHandle, TargetDataHandle);
		ApplyGameplayEffectSpecToOwner(CurrentSpecHandle,CurrentActorInfo,CurrentActivationInfo,EffectSpecHandle);
	}
}
