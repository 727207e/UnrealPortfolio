// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/GA/Skill/GA_BuffTargetCheck.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "EngineUtils.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Character/UPPlayerState.h"
#include "GameFramework/GameStateBase.h"
#include "GAS/AbilityTask/AbilityTask_LivingPlayerTracker.h"
#include "GAS/GA/GA_AttackHitCheck.h"
#include "GAS/GATA/GATA_LivingPlayerTracker.h"
#include "Interface/HUDControllerInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Player/UPPlayerController.h"

class AUPPlayerState;

UGA_BuffTargetCheck::UGA_BuffTargetCheck(): TargetSkillAbilityIndex(0), BuffCount(0)
{
	CurrentTA = AGATA_LivingPlayerTracker::StaticClass();
}

void UGA_BuffTargetCheck::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                          const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                          const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	UAbilityTask_LivingPlayerTracker * AttackTraceTask = UAbilityTask_LivingPlayerTracker::CreateTask(this, CurrentTA);
	AttackTraceTask->OnComplete.AddDynamic(this, &UGA_BuffTargetCheck::OnTraceResultCallback);
	AttackTraceTask->ReadyForActivation();
	//서버가 수정된 정보를 리시브한다.
	Server_SendMessageBuffSlot();
}

void UGA_BuffTargetCheck::Server_SendMessageBuffSlot_Implementation()
{
	for (const auto& player : GetWorld()->GetGameState()->PlayerArray)
	{
		auto HudOwner = Cast<AUPPlayerController>(player->GetOwningController());
		auto Hud = HudOwner->GetHudWidget();
		if(Hud == nullptr)
		{
			UE_LOG(LogTemp,Log,TEXT("Hud Null"));
			continue;
		}
		else
		{
			Hud->Client_BuffProcess();
			// UE_LOG(LogTemp,Log,TEXT("Component %s"),*Hud->GetName());
			// UE_LOG(LogTemp,Log,TEXT("Player %s"),*player->GetName());
			// UE_LOG(LogTemp,Log,TEXT("Controler %s"),*HudOwner->GetName());
		}
		
	}
}

void UGA_BuffTargetCheck::CancelAbility(const FGameplayAbilitySpecHandle Handle,
                                        const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                        bool bReplicateCancelAbility)
{
	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);
}

void UGA_BuffTargetCheck::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UGA_BuffTargetCheck::OnBuffEnd()
{
	BuffSlot->BuffId = -1;
	BuffSlot->SetVisibility(ESlateVisibility::Hidden);

	bool bReplicatedEndAbility = true;
	bool bWasCancelled = false;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicatedEndAbility, bWasCancelled);
}

void UGA_BuffTargetCheck::OnTraceResultCallback(const FGameplayAbilityTargetDataHandle& TargetDataHandle)
{
	BuffCount = 10;
	const FGameplayEffectSpecHandle EffectSpecHandle = MakeOutgoingGameplayEffectSpec(AttackDamageEffect);
	if (EffectSpecHandle.IsValid())
	{
		ApplyGameplayEffectSpecToTarget(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo,EffectSpecHandle,TargetDataHandle);
	}
}