// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Animation/AnimNotify_GASSkillHitCheck.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GAS/Actor/GameplaySkillEventDataRequest.h"
#include "Data/DataAttributeSet/BossDataSet/UPBossSkillAttributeSet.h"

class UAbilitySystemComponent;

FString UAnimNotify_GASSkillHitCheck::GetNotifyName_Implementation() const
{
	return TEXT("GAS");
}

void UAnimNotify_GASSkillHitCheck::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
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

			const UUPBossSkillAttributeSet* TargetAttributeSet = nullptr;

			if (TargetAttributeSetName.IsNone())
			{
				UE_LOG(LogTemp, Log, TEXT("CurNotify Not Set AttributeSet"));
			}
			else
			{
				const TArray<UAttributeSet*> AllAtributes = AbilitySystemComponent->GetSpawnedAttributes();
				for (const UAttributeSet* Attribute : AllAtributes)
				{
					if (Attribute->GetName() == TargetAttributeSetName)
					{
						TargetAttributeSet = Cast<UUPBossSkillAttributeSet>(Attribute);
						break;
					}
				}
				if (nullptr == TargetAttributeSet)
				{
					UE_LOG(LogTemp, Error, TEXT("AnimNotirfy_GasSkillHitCheck can't Find Target AttributeSet"));
					return;
				}
			}

			FGameplayEventData PayloadData;
			
			AGameplaySkillEventDataRequest* ActionData = NewObject<AGameplaySkillEventDataRequest>();
			ActionData->ActionGC = TargetGC;
			ActionData->TargetAttributeSet = TargetAttributeSet;
			ActionData->TargetGenName = TargetGenName;
			PayloadData.Instigator = ActionData;
			PayloadData.OptionalObject = TargetTA.Get();
			

			UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(OwnerActor, TriggerTag,PayloadData);
		}
	}
}