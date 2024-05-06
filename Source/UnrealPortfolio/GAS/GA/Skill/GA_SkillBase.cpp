// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/GA/Skill/GA_SkillBase.h"

#include "AssetSelection.h"
#include "NetworkMessage.h"
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

	if(const AUPMainCharacter* MainCharacter = Cast<AUPMainCharacter>(ActorInfo->AvatarActor.Get()))
	{
		if(AUPPlayerController* PlayerController =  Cast<AUPPlayerController>(MainCharacter->GetController()))
		{
			UUPMainHudWidget* PlayerHud  = Cast<UUPMainHudWidget>( PlayerController->GetHudWidget());

			for(const auto& SKillSlotWidget :  PlayerHud->GetSkillSlotArray())
			{
				if(SKillSlotWidget != nullptr)
				{
					if(TargetSkillAbilityIndex == SKillSlotWidget->TargetInputActionId)
					{
						SKillSlotWidget->OnClickedTargetInputActionKey(Cooldown);
					}
				}
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
	UE_LOG(LogTemp,Log,TEXT("%s"),*GetClass()->GetName());

	for (const auto& SkillData : UUPGameSingleton::Get().SkillDataArray)
	{
		FString TargetSkillName	= SkillData.TargetGameplayAbility->GetName();
		TargetSkillName.ReplaceInline(TEXT("_C"), TEXT(""));
		if(TargetSkillName == ClassName)
		{
			Cooldown = SkillData.CooldownTime;
			MagicPoints = SkillData.MagicPoints;
			TargetSkillAbilityIndex = SkillData.SKillAbilityIndex;
			UE_LOG(LogTemp,Log,TEXT("CollDown %d"), Cooldown);
		}
	}
	
	
	
	//추가 코드 캔슬해야한다.
	
}

