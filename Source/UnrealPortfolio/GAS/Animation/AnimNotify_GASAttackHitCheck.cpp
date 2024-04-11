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
			PayloadData.EventMagnitude = ComboAttackLevel;
			UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(OwnerActor, TriggetTag,PayloadData);
		}
	}
}
