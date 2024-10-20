// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/GA/GA_Attack.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GAS/Attribute/EntityAttributeSet.h"
#include "Character/UPMainCharacter.h"

void UGA_Attack::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                 const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	/** Attackable Setup **/
	AttackableCharacter = CastChecked<IAttackableCharacterInterface>(ActorInfo->AvatarActor.Get());
	if(AttackableCharacter)
	{
		CurrentComboData = AttackableCharacter->GetComboActionData();
	}

	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(ActorInfo->AvatarActor.Get());
	if (nullptr == TargetASC)
	{
		UE_LOG(LogTemp, Error, TEXT("GA_Attack Can't Find ASC"));
		return;
	}

	UEntityAttributeSet* TargetAttribute = const_cast<UEntityAttributeSet*>(TargetASC->GetSet<UEntityAttributeSet>());
	if (nullptr == TargetAttribute)
	{
		UE_LOG(LogTemp, Error, TEXT("GA_Attack Can't Find AttributeSet"));
		return;
	}

	/** PlayAttackTask Ability **/
	UAbilityTask_PlayMontageAndWait* PlayAttackTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(
	this,TEXT("PlayAttack"),
	AttackableCharacter->GetComboActionMontage(),
	TargetAttribute->GetAttackSpeed(),
	GetNextSection());

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
		const FName NextSection = *FString::Printf(TEXT("%s%d"), *CurrentComboData->MontageSectionNamePrefix, CurrentCombo);
		return NextSection;
	}
	else
	{
		return FName();
	}
}

void UGA_Attack::OnCompleteCallback()
{
	constexpr bool bReplicatedEndAbility = true;
	constexpr bool bWasCancelled = false;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicatedEndAbility, bWasCancelled);
}

void UGA_Attack::OnInterruptedCallback()
{
	constexpr bool bReplicatedEndAbility = true;
	constexpr bool bWasCancelled = true;
	EndAbility(CurrentSpecHandle,CurrentActorInfo,CurrentActivationInfo,bReplicatedEndAbility,bWasCancelled);
}

void UGA_Attack::StartComboTimer()
{
	const int32 ComboIndex = CurrentCombo - 1;
	ensure(CurrentComboData->EffectiveFrameCount.IsValidIndex(ComboIndex));
	const float ComboEffectiveTime = CurrentComboData->EffectiveFrameCount[ComboIndex] / CurrentComboData->FrameRate;
	if (ComboEffectiveTime > 0.0f)
	{
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

		AttackableCharacter->AttackEndCallBack();
}

void UGA_Attack::InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo)
{
	if (!ComboTimerHandle.IsValid())
	{
		HasNextComboInput = false;
	}
	else
	{
		HasNextComboInput = true;
	}
}

void UGA_Attack::CheckComboInput()
{
	ComboTimerHandle.Invalidate();
	if (HasNextComboInput)
	{
		MontageJumpToSection(GetNextSection());
		StartComboTimer();
		HasNextComboInput = false;
	}
}
