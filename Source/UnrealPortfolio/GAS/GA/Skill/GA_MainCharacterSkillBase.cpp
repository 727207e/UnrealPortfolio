// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/GA/Skill/GA_MainCharacterSkillBase.h"
#include "Character/UPPlayerState.h"
#include "Game/UPGameSingleton.h"
#include "GAS/AbilityTask/AbilityTask_LookAtMouse.h"
#include "GAS/AbilityTask/AbilityTask_Trace.h"
#include "Interface/HUDControllerInterface.h"
#include "Interface/WeaponControlInterface.h"
#include "UI/UPMainHudWidget.h"
#include "Tag/GameplayTags.h"

class IHUDControllerInterface;

UGA_MainCharacterSkillBase::UGA_MainCharacterSkillBase(): Cooldown(0), MagicPoints(0), TargetSkillAbilityIndex(0)
{
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
	CooldownProcess();
	
	UAbilityTask_LookAtMouse * AttackTraceTask = UAbilityTask_LookAtMouse::CreateTask(this);
	AttackTraceTask->ReadyForActivation();
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

void UGA_MainCharacterSkillBase::OnCompleteCallback()
{
	Super::OnCompleteCallback();
}

void UGA_MainCharacterSkillBase::OnInterruptedCallback()
{
	Super::OnInterruptedCallback();
}

void UGA_MainCharacterSkillBase::CooldownProcess()
{
	const AUPPlayerState* PlayerState = Cast<AUPPlayerState>(CurrentActorInfo->OwnerActor);
	if(IHUDControllerInterface* HudOwner = Cast<IHUDControllerInterface>(PlayerState->GetPlayerController()))
	{
		const TObjectPtr<UUPMainHudWidget> PlayerHud = HudOwner->GetHudWidget();
		if(PlayerHud)
		{
			if(const auto SkillIconWidget = PlayerHud->GetSlotViewWidgetByActionId(TargetSkillAbilityIndex))
			{
				if(!SkillIconWidget->GetCooldownExist())
				{
					SkillIconWidget->OnClickedTargetInputActionKey(Cooldown);
					
					const FGameplayEffectSpecHandle EffectSpecHandle = MakeOutgoingGameplayEffectSpec(UseMpEffect,1.0f);
					EffectSpecHandle.Data->SetSetByCallerMagnitude(TAG_DATA_USE_MP,MagicPoints * -1);
					const FActiveGameplayEffectHandle ActiveGeHandle = ApplyGameplayEffectSpecToOwner(CurrentSpecHandle,CurrentActorInfo,CurrentActivationInfo,EffectSpecHandle);
					
				}
				else
				{
					CancelAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, (false));
					return;
				}
				SkillIconWidget->OnClickedTargetInputActionKey(Cooldown);
			}
		}
	}
}
