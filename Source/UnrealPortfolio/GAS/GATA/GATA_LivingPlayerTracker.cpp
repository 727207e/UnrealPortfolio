// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/GATA/GATA_LivingPlayerTracker.h"

#include "EngineUtils.h"
#include "Character/UPMainCharacter.h"
#include "Tag/GameplayTags.h"
void AGATA_LivingPlayerTracker::ConfirmTargetingAndContinue()
{
	bDestroyOnConfirmation = false;
	for (TActorIterator<AUPMainCharacter> It(GetWorld()); It; ++It)
	{
		AUPMainCharacter* Actor = *It;
        
		if (Actor)
		{
			const bool bHasDeadTag = Actor->GetAbilitySystemComponent()->HasMatchingGameplayTag(TAG_CHARACTER_ISDEAD);
			
			if (!bHasDeadTag)
			{
				FGameplayAbilityTargetData_ActorArray* NewData = new FGameplayAbilityTargetData_ActorArray();
				FGameplayAbilityTargetDataHandle TargetData;
				NewData->TargetActorArray.Add(Actor);
				TargetData.Add(NewData);
				TargetDataReadyDelegate.Broadcast(TargetData);
			}
		}
	}
	
	
}

void AGATA_LivingPlayerTracker::FilterDeadCharacters(TArray<AUPMainCharacter*>& OutActors)
{
	for (TActorIterator<AUPMainCharacter> It(GetWorld()); It; ++It)
	{
		AUPMainCharacter* Actor = *It;
        
		if (Actor && Actor->Implements<UGameplayTagAssetInterface>())
		{
			IGameplayTagAssetInterface* TagInterface = Cast<IGameplayTagAssetInterface>(Actor);
			if (TagInterface)
			{
				FGameplayTagContainer ActorTags;
				TagInterface->GetOwnedGameplayTags(ActorTags);

				if (!ActorTags.HasTag(TAG_CHARACTER_ISDEAD))
				{
					OutActors.Add(Actor);
				}
			}
		}
	}
}
