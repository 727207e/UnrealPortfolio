// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/GATA/GATA_LivingPlayerTracker.h"

#include "EngineUtils.h"
#include "Character/UPMainCharacter.h"
#include "Tag/GameplayTags.h"

void AGATA_LivingPlayerTracker::StartTargeting(UGameplayAbility* Ability)
{
	Super::StartTargeting(Ability);
	
}

void AGATA_LivingPlayerTracker::ConfirmTargetingAndContinue()
{
	TSet<TWeakObjectPtr<AActor>> InTargetObjects;
	FGameplayAbilityTargetData_ActorArray* NewData = new FGameplayAbilityTargetData_ActorArray();
	FGameplayAbilityTargetDataHandle TargetData;
	for (TActorIterator<AUPMainCharacter> It(GetWorld()); It; ++It)
	{
		AUPMainCharacter* Actor = *It;
        
		if (Actor)
		{
			const bool bHasDeadTag = Actor->GetAbilitySystemComponent()->HasMatchingGameplayTag(TAG_CHARACTER_ISDEAD);
			
			if (!bHasDeadTag)
			{
				InTargetObjects.Add(Cast<AActor>(Actor));
			}
		}
	}
	NewData->TargetActorArray = InTargetObjects.Array();
	TargetData.Add(NewData);
	TargetDataReadyDelegate.Broadcast(TargetData);
}
