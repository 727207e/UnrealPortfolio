// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/GA/GA_AttackHitCheck.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GAS/AbilityTask/AbilityTask_Trace.h"
#include "GAS/Actor/GameplayEventDataRequest.h"
#include "GAS/GATA/GATA_Trace.h"
#include "Interface/AttackableCharacterInterface.h"
#include "Data/DataAttributeSet/EntityAttributeSet.h"
#include "Data/DataAttributeSet/EnemyDataSet/NormalEnemy/UPEnemyAttributeSet.h"
#include "Tag/GameplayTags.h"

UGA_AttackHitCheck::UGA_AttackHitCheck()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerExecution;

	CurrentTA = AGATA_Trace::StaticClass();
}

void UGA_AttackHitCheck::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
	CurrentAction = Cast<AGameplayEventDataRequest>(TriggerEventData->Instigator);

	if (TriggerEventData->OptionalObject)
	{
		CurrentTA = Cast<UClass>(TriggerEventData->OptionalObject);
	}

	CurrentAbilityTaskSetup();
}

void UGA_AttackHitCheck::OnTraceResultCallback(const FGameplayAbilityTargetDataHandle& TargetDataHandle)
{
	if (UAbilitySystemBlueprintLibrary::TargetDataHasHitResult(TargetDataHandle, 0))
	{
		const FHitResult HitResult = UAbilitySystemBlueprintLibrary::GetHitResultFromTargetData(TargetDataHandle, 0);


		if(IAttackableCharacterInterface* HitCharacter = Cast<IAttackableCharacterInterface>(HitResult.GetActor()))
		{
			HitCharacter->Hit(GetAvatarActorFromActorInfo()->GetActorLocation(),CurrentAction);
			UAbilitySystemComponent* SourceASC = GetAbilitySystemComponentFromActorInfo_Checked();
			UAbilitySystemComponent* TargetASC =  UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(HitResult.GetActor());
			if(!SourceASC || !TargetASC)
			{
				return;
			}
		
			const UEntityAttributeSet* SourceAttribute = SourceASC->GetSet<UEntityAttributeSet>();
			UEntityAttributeSet* TargetAttribute = const_cast<UEntityAttributeSet*>(TargetASC->GetSet<UEntityAttributeSet>());
			
			if(!SourceAttribute || !TargetAttribute)
			{
				return;
			}
			
			FGameplayEffectSpecHandle EffectSpecHandle = MakeOutgoingGameplayEffectSpec(AttackDamageEffect);
			if(EffectSpecHandle.IsValid())
			{
				EffectSpecHandle.Data->SetSetByCallerMagnitude(TAG_DATA_DAMAGE,-SourceAttribute->GetAttackRate());
				ApplyGameplayEffectSpecToTarget(CurrentSpecHandle,CurrentActorInfo,CurrentActivationInfo,EffectSpecHandle,TargetDataHandle);
			}
			

			if (CurrentAction->ActionGC.IsValid())
			{
				FGameplayCueParameters CueParam;
				CueParam.Location = HitResult.Location;

				TargetASC->ExecuteGameplayCue(CurrentAction->ActionGC, CueParam);
			}
		}
	}

	constexpr bool bReplicatedEndAbility = true;
	constexpr bool bWasCancelled = false;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicatedEndAbility, bWasCancelled);
}

void UGA_AttackHitCheck::CurrentAbilityTaskSetup()
{
	UAbilityTask_Trace * AttackTraceTask = UAbilityTask_Trace::CreateTask(this, CurrentTA);
	AttackTraceTask->OnComplete.AddDynamic(this, &UGA_AttackHitCheck::OnTraceResultCallback);
	AttackTraceTask->ReadyForActivation();
}
