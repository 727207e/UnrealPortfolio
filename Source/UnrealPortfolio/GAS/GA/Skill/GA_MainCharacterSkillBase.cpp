// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/GA/Skill/GA_MainCharacterSkillBase.h"

#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Character/UPPlayerState.h"
#include "Game/UPGameSingleton.h"
#include "GAS/AbilityTask/AbilityTask_LookAtMouse.h"
#include "GAS/AbilityTask/AbilityTask_Trace.h"
#include "Interface/HUDControllerInterface.h"
#include "UI/UPMainHudWidget.h"
#include "Tag/GameplayTags.h"

class IHUDControllerInterface;

UGA_MainCharacterSkillBase::UGA_MainCharacterSkillBase(): Cooldown(0), MagicPoints(0), TargetSkillAbilityIndex(0)
{
	ActivationOwnedTags.AddTag(TAG_PLAYER_STATE_ATTACK_SKILL);	
}

void UGA_MainCharacterSkillBase::SetData()
{
	FString ClassName = GetClass()->GetName();
	ClassName.ReplaceInline(TEXT("_C"), TEXT(""));
	UUPGameSingleton::Get().SkillDataArray;

	for (const auto& SkillData : UUPGameSingleton::Get().SkillDataArray)
	{
		FString TargetSkillName	= SkillData.TargetGameplayAbility->GetName();
		TargetSkillName.ReplaceInline(TEXT("_C"), TEXT(""));
		if(TargetSkillName == ClassName)
		{
			Cooldown = SkillData.CooldownTime;
			MagicPoints = SkillData.MagicPoints;
			TargetSkillAbilityIndex = SkillData.SKillAbilityIndex;
		}
	}
}

void UGA_MainCharacterSkillBase::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                                 const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                                 const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	SetData();
	//if (IsCooldownProcess())
	//{
	//	CancelAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, (false));
	//	return;
	//}
	//else
	{
		//SkillSlotWidget->OnClickedTargetInputActionKey(Cooldown);
		UseMp(ActivationInfo);
		if (!bCantLookAtMouseAbility)
		{
			Cast<ICharacterMovementInterface>(CurrentActorInfo->AvatarActor)->SetMoveBlock(true);
		}
	}
}

void UGA_MainCharacterSkillBase::CancelAbility(const FGameplayAbilitySpecHandle Handle,
                                               const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                               bool bReplicateCancelAbility)
{
	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);
}

void UGA_MainCharacterSkillBase::EndAbility(const FGameplayAbilitySpecHandle Handle,
                                            const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                            bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UGA_MainCharacterSkillBase::InputPressed(const FGameplayAbilitySpecHandle Handle,
                                              const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputPressed(Handle, ActorInfo, ActivationInfo);
}

bool UGA_MainCharacterSkillBase::IsCooldownProcess()
{
	const AUPPlayerState* PlayerState = Cast<AUPPlayerState>(CurrentActorInfo->OwnerActor);
	if(IHUDControllerInterface* HudOwner = Cast<IHUDControllerInterface>(PlayerState->GetPlayerController()))
	{
		const TObjectPtr<UUPMainHudWidget> PlayerHud = HudOwner->GetHudWidget();
		if(PlayerHud)
		{
			const auto SkillIconWidget = PlayerHud->GetSlotViewWidgetByActionId(TargetSkillAbilityIndex);
			if(SkillIconWidget)
			{
				SetSlotWidget(SkillIconWidget);
				if(!SkillSlotWidget->GetCooldownExist())
				{
					return false;
				}
				else
				{
					return true;
				}
			}
		}
	}

	return false;
}

void UGA_MainCharacterSkillBase::SetSlotWidget(USlotViewWidget* TargetSlotViewWidget)
{
	SkillSlotWidget = TargetSlotViewWidget;
}

void UGA_MainCharacterSkillBase::OnCompleteCallback()
{
	Super::OnCompleteCallback();
	Cast<ICharacterMovementInterface>(GetCurrentActorInfo()->AvatarActor)->SetMoveBlock(false);
}

 
void UGA_MainCharacterSkillBase::UseMp(const FGameplayAbilityActivationInfo ActivationInfo)
{
	UAbilitySystemComponent* ASC = GetAbilitySystemComponentFromActorInfo();
	if (ASC && UseMpEffect)
	{
		const FGameplayEffectSpecHandle EffectSpecHandle = MakeOutgoingGameplayEffectSpec(UseMpEffect,1.0f);
		EffectSpecHandle.Data->SetSetByCallerMagnitude(TAG_DATA_USE_MP,MagicPoints * -1);
		const FActiveGameplayEffectHandle ActiveGeHandle = ApplyGameplayEffectSpecToOwner(CurrentSpecHandle,CurrentActorInfo,CurrentActivationInfo,EffectSpecHandle);
	}				
}