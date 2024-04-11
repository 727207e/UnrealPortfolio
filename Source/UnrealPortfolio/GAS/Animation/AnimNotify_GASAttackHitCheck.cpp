// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Animation/AnimNotify_GASAttackHitCheck.h"
#include "AbilitySystemBlueprintLibrary.h"
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
		AActor* OwnerActor = MeshComp->GetOwner();
		if (OwnerActor)
		{
			FGameplayEventData PayloadData;

			// const IAttackableCharacterInterface* Interface =  Cast<IAttackableCharacterInterface>(OwnerActor);
			// if(Interface)
			// {
			// 	UE_LOG(LogTemp,Log,TEXT("xx"));
			// 	Interface->GameplayAbilityActiveToTag(TriggetTag);
			// }
			//UAbilitySystemBlueprintLibrary::

			UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(OwnerActor, TriggetTag,PayloadData);

			// if (::IsValid(OwnerActor))
			// {
			// 	UUPAbilitySystemComponent* AbilitySystemComponent = Cast<UUPAbilitySystemComponent>( UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(OwnerActor));
			// 	if (AbilitySystemComponent != nullptr && IsValidChecked(AbilitySystemComponent))
			// 	{
			// 		FScopedPredictionWindow NewScopedWindow(AbilitySystemComponent, true);
			// 		AbilitySystemComponent->HandleGameplayEvent(TriggetTag, &PayloadData);
			// 	}
			// 	else
			// 	{
			// 		//ABILITY_LOG(Error, TEXT("UAbilitySystemBlueprintLibrary::SendGameplayEventToActor: Invalid ability system component retrieved from Actor %s. EventTag was %s"), *Actor->GetName(), *EventTag.ToString());
			// 	}
			// }
		}
	}
}
