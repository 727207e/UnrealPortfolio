// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/AbilityTask/AbilityTask_SkillGen.h"
#include "GAS/Actor/GameplaySkillEventDataRequest.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "GAS/GATA/GATA_SquareTrace.h"

UAbilityTask_SkillGen::UAbilityTask_SkillGen()
{
}

void UAbilityTask_SkillGen::SpawnAndInitializeTargetActor()
{
	Super::SpawnAndInitializeTargetActor();

	AGATA_SquareTrace* TASquare = Cast<AGATA_SquareTrace>(SpawnedTargetActor);
	if (nullptr == TASquare)
	{
		UE_LOG(LogTemp, Error, TEXT("AbilityTask_SkillGen Failed Cast SpawnedTargetActor To GATA_SaureTrace"));
		return;
	}
	TASquare->CurrentData = CurrentData;
	TASquare->OnTargetDetect.AddDynamic(this, &UAbilityTask_SkillGen::CallBackTargetDetect);
}

void UAbilityTask_SkillGen::CallBackTargetDetect(const FGameplayAbilityTargetDataHandle& DataHandle)
{
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		OnTargetDetect.Broadcast(DataHandle);
	}
}


UAbilityTask_SkillGen* UAbilityTask_SkillGen::CreateTaskWithData(UGameplayAbility* OwningAbility, TSubclassOf<AGATA_Trace> TargetActorClass, TObjectPtr<AGameplaySkillEventDataRequest> Data)
{
	UAbilityTask_SkillGen* NewTask = NewAbilityTask<UAbilityTask_SkillGen>(OwningAbility);
	NewTask->TargetActorClass = TargetActorClass;
	NewTask->CurrentData = Data;
	return NewTask;
}