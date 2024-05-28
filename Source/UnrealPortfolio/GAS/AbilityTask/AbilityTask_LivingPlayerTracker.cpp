// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/AbilityTask/AbilityTask_LivingPlayerTracker.h"

#include "AbilitySystemComponent.h"
#include "GAS/GATA/GATA_LivingPlayerTracker.h"

UAbilityTask_LivingPlayerTracker::UAbilityTask_LivingPlayerTracker()
{
	TargetActorClass = AGATA_LivingPlayerTracker::StaticClass();
}

UAbilityTask_LivingPlayerTracker* UAbilityTask_LivingPlayerTracker::CreateTask(UGameplayAbility* OwningAbility,
	TSubclassOf<AGATA_LivingPlayerTracker> TargetActorClass)
{
	UAbilityTask_LivingPlayerTracker* NewTask = NewAbilityTask<UAbilityTask_LivingPlayerTracker>(OwningAbility);
	NewTask->TargetActorClass = TargetActorClass;
	return NewTask;
}

void UAbilityTask_LivingPlayerTracker::Activate()
{
	Super::Activate();
	SpawnAndInitializeTargetActor();
}

void UAbilityTask_LivingPlayerTracker::OnDestroy(bool AbilityEnded)
{
	if (SpawnedTargetActor)
	{
		SpawnedTargetActor->Destroy();
	}
	Super::OnDestroy(AbilityEnded);
}

void UAbilityTask_LivingPlayerTracker::SpawnAndInitializeTargetActor()
{
	SpawnedTargetActor = Cast<AGATA_LivingPlayerTracker>(Ability->GetWorld()->SpawnActorDeferred<AGameplayAbilityTargetActor>(AGATA_LivingPlayerTracker::StaticClass(),FTransform::Identity,nullptr,nullptr,ESpawnActorCollisionHandlingMethod::AlwaysSpawn));
	if(SpawnedTargetActor)
	{
		SpawnedTargetActor->TargetDataReadyDelegate.AddUObject(this, &UAbilityTask_LivingPlayerTracker::OnTargetDataReadyCallback);
	}
}

void UAbilityTask_LivingPlayerTracker::FinalizeTargetActor()
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


void UAbilityTask_LivingPlayerTracker::OnTargetDataReadyCallback(const FGameplayAbilityTargetDataHandle& DataHandle)
{
	
	if(ShouldBroadcastAbilityTaskDelegates())
	{
		OnComplete.Broadcast(DataHandle);
	}
	EndTask();
}
