// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/GA/GA_Attack.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Character/UPMainCharacter.h"

void UGA_Attack::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                 const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	/** Attackable Setup **/
	AttackableCharacter = CastChecked<IAttackableCharacterInterface>(ActorInfo->AvatarActor.Get());
	if(AttackableCharacter)
	{
		UE_LOG(LogTemp,Log,TEXT("CurrentComboData"));
		CurrentComboData = AttackableCharacter->GetComboActionData();
	}

	/** PlayAttackTask Ability **/
	UAbilityTask_PlayMontageAndWait* PlayAttackTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(
	this,TEXT("PlayAttack"),
	AttackableCharacter->GetComboActionMontage(),
	1.0f,GetNextSection());
	PlayAttackTask->OnCompleted.AddDynamic(this,&UGA_Attack::OnCompleteCallback);
	PlayAttackTask->OnInterrupted.AddDynamic(this,&UGA_Attack::OnInterruptedCallback);
	PlayAttackTask->ReadyForActivation();

	if (CurrentComboData)
	{
		StartComboTimer();
	}
}

FName UGA_Attack::GetNextSection()
{
	//Data Code Need Change ****
	if (CurrentComboData)
	{
		CurrentCombo = FMath::Clamp(CurrentCombo + 1, 1, CurrentComboData->MaxComboCount);
		FName NextSection = *FString::Printf(TEXT("%s%d"), *CurrentComboData->MontageSectionNamePrefix, CurrentCombo);
		return NextSection;
	}
	else
	{
		return FName();
	}
}

void UGA_Attack::OnCompleteCallback()
{
	bool bReplicatedEndAbility = true;
	bool bWasCancelled = false;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicatedEndAbility, bWasCancelled);
}

void UGA_Attack::OnInterruptedCallback()
{
	bool bReplicatedEndAbility = true;
	bool bWasCancelled = true;
	EndAbility(CurrentSpecHandle,CurrentActorInfo,CurrentActivationInfo,bReplicatedEndAbility,bWasCancelled);
}

void UGA_Attack::StartComboTimer()
{
	int32 ComboIndex = CurrentCombo - 1;
	ensure(CurrentComboData->EffectiveFrameCount.IsValidIndex(ComboIndex));
	const float ComboEffectiveTime = CurrentComboData->EffectiveFrameCount[ComboIndex] / CurrentComboData->FrameRate;
	if (ComboEffectiveTime > 0.0f)
	{
		UE_LOG(LogTemp,Log,TEXT("ComboEffectiveTime"));
		GetWorld()->GetTimerManager().SetTimer(ComboTimerHandle, this, &UGA_Attack::CheckComboInput, ComboEffectiveTime, false);
	}
	
}

void UGA_Attack::CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                               const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility)
{
	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);
}

void UGA_Attack::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
		Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
    	CurrentComboData = nullptr;
    	CurrentCombo = 0;
    	HasNextComboInput = false;
}

void UGA_Attack::InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo)
{
	if (!ComboTimerHandle.IsValid())
	{
		UE_LOG(LogTemp,Log,TEXT("false"));
		HasNextComboInput = false;
	}
	else
	{
		UE_LOG(LogTemp,Log,TEXT("true"));
		HasNextComboInput = true;
	}
}

void UGA_Attack::CheckComboInput()
{
	ComboTimerHandle.Invalidate();
	if (HasNextComboInput)
	{
		UE_LOG(LogTemp,Log,TEXT("CheckComboInput"));
		MontageJumpToSection(GetNextSection());
		StartComboTimer();
		HasNextComboInput = false;
	}
}
