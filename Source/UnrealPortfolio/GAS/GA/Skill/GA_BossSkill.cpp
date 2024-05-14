// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/GA/Skill/GA_BossSkill.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Data/DataAttributeSet/BossDataSet/UPBossSkillAttributeSet.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"

UGA_BossSkill::UGA_BossSkill()
{
	IndexNumber = 0;
}

void UGA_BossSkill::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	if (SkillSectionList.Num() > 0)
	{
		TargetMontageSectionName = SkillSectionList[IndexNumber];
		IndexNumber++;
	}
	SourceASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(ActorInfo->AvatarActor.Get());
	const TArray<UAttributeSet*> AllAtributes = SourceASC->GetSpawnedAttributes();

	for (const UAttributeSet* Attribute : AllAtributes)
	{
		if (Attribute->GetName() == FString::FromInt(SkillNumber))
		{
			SourceAttribute = Cast<UUPBossSkillAttributeSet>(Attribute);
			break;
		}
	}

	if (nullptr == SourceAttribute)
	{
		UE_LOG(LogTemp, Error, TEXT("GA_BossSkill Can't Find AttributeSet"));
		return;
	}
	
	AttackSpeed = SourceAttribute->GetAttackSpeed();

	if (AttackSpeed == 0)
	{
		UE_LOG(LogTemp, Error, TEXT("GA_BossSkill AttackSpeed Can't Be 0"));
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
	}

	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UGA_BossSkill::OnCompleteCallback()
{
	if (IndexNumber < SkillSectionList.Num())
	{
		TargetMontageSectionName = SkillSectionList[IndexNumber];
		IndexNumber++;

		PlayNextMontage();
	}

	else
	{
		bool bReplicatedEndAbility = true;
		bool bWasCancelled = false;
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicatedEndAbility, bWasCancelled);
	}
}

void UGA_BossSkill::PlayNextMontage()
{
	UAbilityTask_PlayMontageAndWait* PlayAttackTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(
		this, TEXT("PlayerSkill"), TargetMontage, AttackSpeed, TargetMontageSectionName);

	PlayAttackTask->OnCompleted.AddDynamic(this, &UGA_BossSkill::OnCompleteCallback);
	PlayAttackTask->OnInterrupted.AddDynamic(this, &UGA_BossSkill::OnInterruptedCallback);
	PlayAttackTask->ReadyForActivation();
}
