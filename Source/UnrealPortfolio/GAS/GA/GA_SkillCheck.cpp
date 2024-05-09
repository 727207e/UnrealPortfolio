// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/GA/GA_SkillCheck.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GAS/AbilityTask/AbilityTask_SkillGen.h"
#include "GAS/Actor/GameplaySkillEventDataRequest.h"
#include "GAS/GATA/GATA_Trace.h"
#include "Interface/AttackableCharacterInterface.h"
#include "Data/DataAttributeSet/EntityAttributeSet.h"
#include "Data/DataAttributeSet/EnemyDataSet/NormalEnemy/UPEnemyAttributeSet.h"
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
	//히트 판정 (종료 아님)
	UE_LOG(LogTemp, Error, TEXT("Not OVer Target Detect"));
}

void UGA_SkillCheck::OnTraceResultCallback(const FGameplayAbilityTargetDataHandle& TargetDataHandle)
{
	//히트 판정 (종료)
	UE_LOG(LogTemp, Error, TEXT("OVer Target Detect"));

	//if (UAbilitySystemBlueprintLibrary::TargetDataHasHitResult(TargetDataHandle, 0))
	//{
	//	const FHitResult HitResult = UAbilitySystemBlueprintLibrary::GetHitResultFromTargetData(TargetDataHandle, 0);

	//	if (IAttackableCharacterInterface* HitCharacter = Cast<IAttackableCharacterInterface>(HitResult.GetActor()))
	//	{
	//		HitCharacter->Hit(GetAvatarActorFromActorInfo()->GetActorLocation(), nullptr);
	//		UAbilitySystemComponent* SourceASC = GetAbilitySystemComponentFromActorInfo_Checked();
	//		UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(HitResult.GetActor());
	//		if (!SourceASC || !TargetASC)
	//		{
	//			return;
	//		}

	//		const UEntityAttributeSet* SourceAttribute = SourceASC->GetSet<UEntityAttributeSet>();
	//		UEntityAttributeSet* TargetAttribute = const_cast<UEntityAttributeSet*>(TargetASC->GetSet<UEntityAttributeSet>());

	//		if (!SourceAttribute || !TargetAttribute)
	//		{
	//			return;
	//		}

	//		FGameplayEffectSpecHandle EffectSpecHandle = MakeOutgoingGameplayEffectSpec(AttackDamageEffect);
	//		if (EffectSpecHandle.IsValid())
	//		{
	//			EffectSpecHandle.Data->SetSetByCallerMagnitude(TAG_DATA_DAMAGE, -SourceAttribute->GetAttackRate());
	//			ApplyGameplayEffectSpecToTarget(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, EffectSpecHandle, TargetDataHandle);
	//		}

	//		if (CurrentAction->ActionGC.IsValid())
	//		{
	//			FGameplayCueParameters CueParam;
	//			CueParam.Location = HitResult.Location;

	//			TargetASC->ExecuteGameplayCue(CurrentAction->ActionGC, CueParam);
	//		}
	//	}
	//}

	constexpr bool bReplicatedEndAbility = true;
	constexpr bool bWasCancelled = false;

	UE_LOG(LogTemp, Error, TEXT("GA Skill TA Trigger Enter"));
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicatedEndAbility, bWasCancelled);
}