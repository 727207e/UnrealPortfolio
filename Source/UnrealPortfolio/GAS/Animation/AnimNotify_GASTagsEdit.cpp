// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Animation/AnimNotify_GASTagsEdit.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GAS/Actor/GameplayEventDataRequest.h"

void UAnimNotify_GASTagsEdit::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (AActor* OwnerActor = MeshComp->GetOwner())
	{
		UAbilitySystemComponent* AbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OwnerActor);
		if (nullptr == AbilitySystemComponent)
		{
			return;
		}

		FGameplayTagContainer TagContainer;
		for (FGameplayTag Tag : TagList)
		{
			TagContainer.AddTag(Tag);
		}

		if (bIsAddTag)
		{
			AbilitySystemComponent->AddLooseGameplayTags(TagContainer);
		}
		else
		{
			AbilitySystemComponent->RemoveLooseGameplayTags(TagContainer);
		}

	}
}