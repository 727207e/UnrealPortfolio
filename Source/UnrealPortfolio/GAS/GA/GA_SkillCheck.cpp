// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/GA/GA_SkillCheck.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GAS/AbilityTask/AbilityTask_SkillGen.h"
#include "GAS/Actor/GameplaySkillEventDataRequest.h"
#include "GAS/GATA/GATA_Trace.h"
#include "Interface/AttackableCharacterInterface.h"
#include "Data/DataAttributeSet/EntityAttributeSet.h"
#include "Data/DataAttributeSet/BossDataSet/UPBossSkillAttributeSet.h"
#include "Tag/GameplayTags.h"

UGA_SkillCheck::UGA_SkillCheck()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerExecution;
}

void UGA_SkillCheck::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	CurrentData = Cast<AGameplaySkillEventDataRequest>(TriggerEventData->Instigator);
	CurrentTA = Cast<UClass>(TriggerEventData->OptionalObject);

	UAbilityTask_SkillGen* AttackTraceTask = UAbilityTask_SkillGen::CreateTaskWithData(this, CurrentTA, CurrentData);
	AttackTraceTask->OnTargetDetect.AddDynamic(this, &UGA_SkillCheck::OnTargetDetect);
	AttackTraceTask->OnComplete.AddDynamic(this, &UGA_SkillCheck::OnTraceResultCallback);
	AttackTraceTask->ReadyForActivation();
}

void UGA_SkillCheck::OnTargetDetect(const FGameplayAbilityTargetDataHandle& TargetDataHandle)
{
	if (UAbilitySystemBlueprintLibrary::TargetDataHasHitResult(TargetDataHandle, 0))
	{
		int TargetNumber = UAbilitySystemBlueprintLibrary::GetDataCountFromTargetData(TargetDataHandle);

		for (int Index = 0; Index < TargetNumber; Index++)
		{
			AttackTargetWithHitResult(TargetDataHandle, Index);
		}
	}

	else if (UAbilitySystemBlueprintLibrary::TargetDataHasActor(TargetDataHandle, 0))
	{
		for (AActor* Target : UAbilitySystemBlueprintLibrary::GetActorsFromTargetData(TargetDataHandle, 0))
		{
			AttackTargetWithActorInfo(TargetDataHandle, Target);
		}
	}
}

void UGA_SkillCheck::OnTraceResultCallback(const FGameplayAbilityTargetDataHandle& TargetDataHandle)
{
	OnTargetDetect(TargetDataHandle);

	constexpr bool bReplicatedEndAbility = true;
	constexpr bool bWasCancelled = false;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicatedEndAbility, bWasCancelled);
}

void UGA_SkillCheck::AttackTargetWithHitResult(const FGameplayAbilityTargetDataHandle& TargetDataHandle, int32 IndexNumber)
{
	const FHitResult HitResult = UAbilitySystemBlueprintLibrary::GetHitResultFromTargetData(TargetDataHandle, IndexNumber);

	if (IAttackableCharacterInterface* HitCharacter = Cast<IAttackableCharacterInterface>(HitResult.GetActor()))
	{
		HitCharacter->Hit(GetAvatarActorFromActorInfo()->GetActorLocation(), nullptr);
		UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(HitResult.GetActor());
		if (!TargetASC)
		{
			return;
		}

		UEntityAttributeSet* TargetAttribute = const_cast<UEntityAttributeSet*>(TargetASC->GetSet<UEntityAttributeSet>());

		if (!TargetAttribute)
		{
			return;
		}

		if (nullptr == CurrentData->TargetAttributeSet)
		{
			return;
		}

		FGameplayEffectSpecHandle EffectSpecHandle = MakeOutgoingGameplayEffectSpec(AttackDamageEffect);
		if (EffectSpecHandle.IsValid())
		{
			EffectSpecHandle.Data->SetSetByCallerMagnitude(TAG_DATA_DAMAGE, -CurrentData->TargetAttributeSet->GetDamage());
			ApplyGameplayEffectSpecToTarget(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, EffectSpecHandle, TargetDataHandle);
		}

		if (CurrentData->ActionGC.IsValid())
		{
			FGameplayCueParameters CueParam;
			CueParam.Location = HitResult.Location;

			TargetASC->ExecuteGameplayCue(CurrentData->ActionGC, CueParam);
		}
	}
}

void UGA_SkillCheck::AttackTargetWithActorInfo(const FGameplayAbilityTargetDataHandle& TargetDataHandle, AActor* Target)
{
	if (IAttackableCharacterInterface* HitCharacter = Cast<IAttackableCharacterInterface>(Target))
	{
		HitCharacter->Hit(GetAvatarActorFromActorInfo()->GetActorLocation(), nullptr);
		UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Target);
		if (!TargetASC)
		{
			return;
		}

		UEntityAttributeSet* TargetAttribute = const_cast<UEntityAttributeSet*>(TargetASC->GetSet<UEntityAttributeSet>());

		if (!TargetAttribute)
		{
			return;
		}

		if (nullptr == CurrentData->TargetAttributeSet)
		{
			return;
		}

		FGameplayEffectSpecHandle EffectSpecHandle = MakeOutgoingGameplayEffectSpec(AttackDamageEffect);
		if (EffectSpecHandle.IsValid())
		{
			EffectSpecHandle.Data->SetSetByCallerMagnitude(TAG_DATA_DAMAGE, -CurrentData->TargetAttributeSet->GetDamage());
			ApplyGameplayEffectSpecToTarget(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, EffectSpecHandle, TargetDataHandle);
		}

		if (CurrentData->ActionGC.IsValid())
		{
			FGameplayCueParameters CueParam;
			CueParam.Location = Target->GetActorLocation();

			TargetASC->ExecuteGameplayCue(CurrentData->ActionGC, CueParam);
		}
	}
}


