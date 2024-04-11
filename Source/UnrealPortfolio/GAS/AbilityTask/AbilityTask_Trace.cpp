// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/AbilityTask/AbilityTask_Trace.h"

#include "AbilitySystemComponent.h"

UAbilityTask_Trace::UAbilityTask_Trace()
{
}

UAbilityTask_Trace* UAbilityTask_Trace::CreateTask(UGameplayAbility* OwningAbility, TSubclassOf<AGATA_Trace> TargetActorClass)
{
	UAbilityTask_Trace* NewTask = NewAbilityTask<UAbilityTask_Trace>(OwningAbility);
	NewTask->TargetActorClass = TargetActorClass;
	return NewTask;
}



void UAbilityTask_Trace::Activate()
{
	Super::Activate();

	SpawnAndInitializeTargetActor();
	FinalizeTargetActor();

	SetWaitingOnAvatar();
}

void UAbilityTask_Trace::OnDestroy(bool AbilityEnded)
{
	
	if (SpawnedTargetActor)
	{
		SpawnedTargetActor->Destroy();
	}

	Super::OnDestroy(AbilityEnded);
}

void UAbilityTask_Trace::SpawnAndInitializeTargetActor()
{
	UE_LOG(LogTemp,Log,TEXT("SpawnAndInitializeTargetActor"));
	SpawnedTargetActor = Cast<AGATA_Trace>(Ability->GetWorld()->SpawnActorDeferred<AGameplayAbilityTargetActor>(TargetActorClass,FTransform::Identity,nullptr,nullptr,ESpawnActorCollisionHandlingMethod::AlwaysSpawn));
	if(SpawnedTargetActor)
	{
		SpawnedTargetActor->SetShowDebug(true);
		SpawnedTargetActor->TargetDataReadyDelegate.AddUObject(this, &UAbilityTask_Trace::OnTargetDataReadyCallback);
	}
}

void UAbilityTask_Trace::FinalizeTargetActor()
{
	UAbilitySystemComponent* ASC = Cast<UAbilitySystemComponent>(AbilitySystemComponent.Get());
	if (ASC)
	{
		const FTransform SpawnTransform = ASC->GetAvatarActor()->GetTransform();
		SpawnedTargetActor->FinishSpawning(SpawnTransform);
    
		ASC->SpawnedTargetActors.Push(SpawnedTargetActor);
		SpawnedTargetActor->StartTargeting(Ability);
		SpawnedTargetActor->ConfirmTargeting();
	}
}

//종료
void UAbilityTask_Trace::OnTargetDataReadyCallback(const FGameplayAbilityTargetDataHandle& DataHandle)
{
	UE_LOG(LogTemp,Log,TEXT("OnTargetDataReadyCallback"));
	if(ShouldBroadcastAbilityTaskDelegates())
	{
		OnComplete.Broadcast(DataHandle);
	}

	EndTask();
}

