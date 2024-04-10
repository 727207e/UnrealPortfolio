// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/GA/GA_Attack.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Character/UPMainCharacter.h"

void UGA_Attack::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                 const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	//모션재생 어빌리티 테스크
	AttackableCharacter = CastChecked<IAttackableCharacterInterface>(ActorInfo->AvatarActor.Get());
	MovementInterface = CastChecked<ICharacterMovementInterface>(ActorInfo->AvatarActor.Get());
	MovementInterface->SetCharacterMovementMod(MOVE_None);
	UAbilityTask_PlayMontageAndWait* PlayAttackTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(
		this,TEXT("PlayAttack"), AttackableCharacter->GetComboActionMontage(),1.0f,GetNextSection());
	PlayAttackTask->OnCompleted.AddDynamic(this,&UGA_Attack::OnCompleteCallback);
	PlayAttackTask->OnInterrupted.AddDynamic(this,&UGA_Attack::OnInterruptedCallback);
	PlayAttackTask->ReadyForActivation();

}

FName UGA_Attack::GetNextSection()
{
	CurrentCombo = FMath::Clamp(CurrentCombo + 1, 1, 3);
	//사용CurrentCombo법 주의
	const FName NextSection = *FString::Printf(TEXT("%s%d"),TEXT("ComboAttack"),CurrentCombo);
	return NextSection;
}

void UGA_Attack::OnCompleteCallback()
{
	AUPMainCharacter* AabCharacterBase = CastChecked<AUPMainCharacter>(CurrentActorInfo->AvatarActor.Get());
	AabCharacterBase->SetCharacterMovementMod(MOVE_Walking);
	//리플리케이션에대한 사용여부 (네트워크)
	bool bReplicatedEndAbility = true;
	//취소 여부
	bool bWasCancelled = false;
	EndAbility(CurrentSpecHandle,CurrentActorInfo,CurrentActivationInfo,bReplicatedEndAbility,bWasCancelled);
}

void UGA_Attack::OnInterruptedCallback()
{
	bool bReplicatedEndAbility = true;
	bool bWasCancelled = true;
	EndAbility(CurrentSpecHandle,CurrentActorInfo,CurrentActivationInfo,bReplicatedEndAbility,bWasCancelled);
	
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
}

void UGA_Attack::InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputPressed(Handle, ActorInfo, ActivationInfo);
}
