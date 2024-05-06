// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/GA/Skill/GA_SkillBase.h"

#include "Character/UPMainCharacter.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Game/UPGameSingleton.h"
#include "Player/UPPlayerController.h"

UGA_SkillBase::UGA_SkillBase(): AttackableCharacter(nullptr), MovementCharacter(nullptr), TargetMontage(nullptr),
                                MagicPoints(0)
{
	
}

void UGA_SkillBase::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                    const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	SetData();
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	AttackableCharacter = CastChecked<IAttackableCharacterInterface>(ActorInfo->AvatarActor.Get());
	if(IHUDControllerInterface* HudOwner = Cast<IHUDControllerInterface>(ActorInfo->AvatarActor.Get()))
	{
		const TObjectPtr<UUPMainHudWidget> PlayerHud = HudOwner->GetHudWidget();
		if(const auto SkillIconWidget = PlayerHud->GetSlotViewWidgetByActionId(TargetSkillAbilityIndex))
		{
			if(!SkillIconWidget->GetCooldownExist())
			{
				SkillIconWidget->OnClickedTargetInputActionKey(Cooldown);
			}
			else
			{
				CancelAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
				return;
			}
		}
	
	}
	
	if(TargetMontage)
	{
		/** PlayAttackTask Ability **/
		UAbilityTask_PlayMontageAndWait* PlayAttackTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(
			this,TEXT("PlayerSkill"),TargetMontage,1.0f);
	
		PlayAttackTask->OnCompleted.AddDynamic(this,&UGA_SkillBase::OnCompleteCallback);
		PlayAttackTask->OnInterrupted.AddDynamic(this,&UGA_SkillBase::OnInterruptedCallback);
		PlayAttackTask->ReadyForActivation();
	}
}

void UGA_SkillBase::CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility)
{
	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);
}

void UGA_SkillBase::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	AttackableCharacter->AttackEndCallBack();
}

void UGA_SkillBase::InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputPressed(Handle, ActorInfo, ActivationInfo);
}

void UGA_SkillBase::OnCompleteCallback()
{
	bool bReplicatedEndAbility = true;
	bool bWasCancelled = false;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicatedEndAbility, bWasCancelled);
}

void UGA_SkillBase::OnInterruptedCallback()
{
	bool bReplicatedEndAbility = true;
	bool bWasCancelled = true;
	EndAbility(CurrentSpecHandle,CurrentActorInfo,CurrentActivationInfo,bReplicatedEndAbility,bWasCancelled);
}

void UGA_SkillBase::SetData()
{
	FString  ClassName = GetClass()->GetName();
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
	
	
	
	//추가 코드 캔슬해야한다.
	
}

