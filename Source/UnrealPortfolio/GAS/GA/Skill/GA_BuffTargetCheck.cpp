// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/GA/Skill/GA_BuffTargetCheck.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "EngineUtils.h"
#include "Character/UPPlayerState.h"
#include "GAS/AbilityTask/AbilityTask_LivingPlayerTracker.h"
#include "GAS/GA/GA_AttackHitCheck.h"
#include "GAS/GATA/GATA_LivingPlayerTracker.h"
#include "Interface/AttackableCharacterInterface.h"
#include "Interface/HUDControllerInterface.h"
#include "Tag/GameplayTags.h"

class IAttackableCharacterInterface;
class AUPPlayerState;

UGA_BuffTargetCheck::UGA_BuffTargetCheck()
{
	CurrentTA = AGATA_LivingPlayerTracker::StaticClass();
}

void UGA_BuffTargetCheck::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                          const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                          const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	SimpleTargetMaker();
	// UAbilityTask_LivingPlayerTracker * AttackTraceTask = UAbilityTask_LivingPlayerTracker::CreateTask(this, CurrentTA);
	// AttackTraceTask->OnComplete.AddDynamic(this, &UGA_BuffTargetCheck::OnTraceResultCallback);
	// AttackTraceTask->ReadyForActivation();
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

void UGA_BuffTargetCheck::OnTraceResultCallback(const FGameplayAbilityTargetDataHandle& TargetDataHandle)
{
	if (UAbilitySystemBlueprintLibrary::TargetDataHasHitResult(TargetDataHandle, 0))
	{
		TargetData = TargetDataHandle;
	}
}

void UGA_BuffTargetCheck::ApplyBuff()
{
	if(TargetData != nullptr)
	{
		BuffSlot->OnClickedTargetInputActionKey(10);
		BuffSlot->SetVisibility(ESlateVisibility::Visible);
		BuffSlot->CooldownFinishDelegate.AddDynamic(this,&UGA_BuffTargetCheck::OnBuffEnd);
		const FGameplayEffectSpecHandle EffectSpecHandle = MakeOutgoingGameplayEffectSpec(AttackDamageEffect);
		if (EffectSpecHandle.IsValid())
		{
			//ApplyGameplayEffectSpecToTarget(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, EffectSpecHandle, TargetData);
			ApplyGameplayEffectSpecToOwner(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, EffectSpecHandle);
		}
	}

}

void UGA_BuffTargetCheck::SimpleTargetMaker()
{
	for (TActorIterator<AUPMainCharacter> It(GetWorld()); It; ++It)
	{
		AUPMainCharacter* Actor = *It;
        
		if (Actor)
		{
			const bool bHasDeadTag = Actor->GetAbilitySystemComponent()->HasMatchingGameplayTag(TAG_CHARACTER_ISDEAD);
			
			if (!bHasDeadTag)
			{
				if(Actor->HasAuthority())
				{
					SimepleProrcess(Actor);
				}
				else
				{
					OnRep_PlayerState();
				}
				
			}
		}
	}
}

void UGA_BuffTargetCheck::SimepleProrcess(AUPMainCharacter* MainCharacter)
{
	const AUPPlayerState* PlayerState = Cast<AUPPlayerState>(MainCharacter);
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

void UGA_BuffTargetCheck::OnRep_PlayerState()
{
	
}
