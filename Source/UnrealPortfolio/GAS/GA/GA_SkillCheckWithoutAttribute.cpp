// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/GA/GA_SkillCheckWithoutAttribute.h"
#include "Interface/AttackReplaceDataInterface.h"
#include "Interface/AttackableCharacterInterface.h"
#include "GAS/Actor/GameplaySkillEventDataRequest.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GAS/AbilityTask/AbilityTask_SkillGen.h"
#include "Tag/GameplayTags.h"

UGA_SkillCheckWithoutAttribute::UGA_SkillCheckWithoutAttribute()
{
}

void UGA_SkillCheckWithoutAttribute::AttackSequence(const FGameplayAbilityTargetDataHandle& TargetDataHandle, FVector TargetLocation, AActor* TargetActor)
{
	if (IAttackableCharacterInterface* HitCharacter = Cast<IAttackableCharacterInterface>(TargetActor))
	{
		IAttackReplaceDataInterface* AttackData = Cast<IAttackReplaceDataInterface>(AttackTraceTask->GetSpawnedTA());
		if (nullptr == AttackData)
		{
			UE_LOG(LogTemp, Error, TEXT("GA_SkillCheckWithoutAttribute : Current TA is Not AttackReplaceDataInterface"));
			return;
		}


		HitCharacter->Hit(GetAvatarActorFromActorInfo()->GetActorLocation(), nullptr);
		UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
		if (!TargetASC)
		{
			return;
		}

		FGameplayEffectSpecHandle EffectSpecHandle = MakeOutgoingGameplayEffectSpec(AttackDamageEffect);
		if (EffectSpecHandle.IsValid())
		{
			EffectSpecHandle.Data->SetSetByCallerMagnitude(TAG_DATA_DAMAGE, -AttackData->GetAttackValue());
			ApplyGameplayEffectSpecToTarget(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, EffectSpecHandle, TargetDataHandle);
		}

		if (CurrentData->ActionGC.IsValid())
		{
			FGameplayCueParameters CueParam;
			CueParam.Location = TargetLocation;

			TargetASC->ExecuteGameplayCue(CurrentData->ActionGC, CueParam);
		}
	}
}