// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotify_PlayAttackEffect.h"
#include "Character/UPBattleBaseCharacter.h"

void UAnimNotify_PlayAttackEffect::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (MeshComp)
	{
		if (AActor* OwnerActor = MeshComp->GetOwner())
		{
			AUPBattleBaseCharacter* BattleCharacter = Cast<AUPBattleBaseCharacter>(OwnerActor);
			if (BattleCharacter)
			{
				if (BattleCharacter->OnAttackEffect.IsBound())
				{
					BattleCharacter->OnAttackEffect.Broadcast(TriggerTag);
				}
			}
		}
	}
}