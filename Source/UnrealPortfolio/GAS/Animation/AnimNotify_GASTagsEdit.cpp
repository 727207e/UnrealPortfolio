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
		for (FName TagName : TagList)
		{
			TagContainer.AddTag(FGameplayTag::RequestGameplayTag(TagName));
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