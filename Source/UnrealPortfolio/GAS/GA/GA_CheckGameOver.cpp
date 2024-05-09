// Fill out your copyright notice in the Description page of Project Settings.
#include "GAS/GA/GA_CheckGameOver.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "EngineUtils.h"
#include "Character/UPMainCharacter.h"
#include "Character/UPPlayerState.h"
#include "Interface/BossInterface.h"

UGA_CheckGameOver::UGA_CheckGameOver(): PlayerMaxCount(0), PlayerCurrentDeadCount(0)
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UGA_CheckGameOver::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                        const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                        const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	CheckDeadTargetCharacter();
}

void UGA_CheckGameOver::CheckDeadTargetCharacter()
{
	for (TActorIterator<AUPBattleBaseCharacter> It(GetWorld()); It; ++It)
	{
		IBossInterface* IBoss = Cast<IBossInterface>(*It);
		if(IBoss)
		{
			if (UAbilitySystemComponent* ASC = IBoss->GetBossAbilitySystemComponent())
			{
				ASC->RegisterGameplayTagEvent(DeadTag,EGameplayTagEventType::NewOrRemoved).AddUObject(this,&ThisClass::BossIsDead);
				break;
			}
		}
		else
		{
			IUPPossessCharacterInterface* IPlayer = Cast<IUPPossessCharacterInterface>(*It);
			if(IPlayer)
			{
				AUPPlayerState* PS =  IPlayer->GetUPPlayerState();
				if(PS)
				{
					UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
					if (ASC)
					{
						ASC->RegisterGameplayTagEvent(DeadTag,EGameplayTagEventType::NewOrRemoved).AddUObject(this,&ThisClass::OnPlayerIsDead);
					}
				}
			}
			
		}
	}
	
	GetAbilitySystemComponentFromActorInfo()->RegisterGameplayTagEvent(BossDeadTag,EGameplayTagEventType::NewOrRemoved).AddUObject(this,&ThisClass::BossIsDead);
}

void UGA_CheckGameOver::OnPlayerIsDead(const FGameplayTag TargetTag, int32 NewCount)
{
	const FString TagString = TargetTag.ToString();
	PlayerCurrentDeadCount += NewCount;
	UE_LOG(LogTemp,Log,TEXT("%s : %d"),*TagString,PlayerCurrentDeadCount);
	if(PlayerCurrentDeadCount >= PlayerMaxCount)
	{
		/** Test Code **/
		UE_LOG(LogTemp,Log,TEXT("Player Team Loss"));
		CancelAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, (false));
	}
}

void UGA_CheckGameOver::BossIsDead(const FGameplayTag TargetTag, int32 NewCount)
{
	/** Test Code **/
	UE_LOG(LogTemp,Log,TEXT("Player Team Win"));
	CancelAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, (false));
}
