// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/UPEnemyTargetFoundAnimNotify.h"
#include "Animation/UPEnemyAnimInstance.h"

void UUPEnemyTargetFoundAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (MeshComp)
	{
		AActor* OwnerActor = MeshComp->GetOwner();
		if (!OwnerActor)
		{
			return;
		}

		UUPEnemyAnimInstance* EnemyAnimInstance = Cast<UUPEnemyAnimInstance>(MeshComp->GetAnimInstance());
		if (EnemyAnimInstance)
		{
			EnemyAnimInstance->SetIsTargetLock(true);
		}
	}
}