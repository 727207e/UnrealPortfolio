// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Animation/AnimNotify_GASAttackHitCheck.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GAS/Actor/GameplayEventDataRequest.h"

class UAbilitySystemComponent;

FString UAnimNotify_GASAttackHitCheck::GetNotifyName_Implementation() const
{
	return TEXT("GAS");
}

void UAnimNotify_GASAttackHitCheck::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                           const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (MeshComp)
	{
		if (AActor* OwnerActor = MeshComp->GetOwner())
		{
			UAbilitySystemComponent* AbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OwnerActor);
			if (nullptr == AbilitySystemComponent)
			{
				return;
			}

			FGameplayEventData PayloadData;
			
			/** Set Event Data **/
			PayloadData.EventMagnitude = AttackLevel;
			AGameplayEventDataRequest* ActionData = NewObject<AGameplayEventDataRequest>();
			ActionData->ActionId = ActionId;
			ActionData->ActionRowName = ActionRowName;
			ActionData->ActionGC = TargetGC;
			PayloadData.Instigator = ActionData;
			PayloadData.OptionalObject = TargetTA.Get();
			
			UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(OwnerActor, TriggerTag,PayloadData);
		}
	}
}