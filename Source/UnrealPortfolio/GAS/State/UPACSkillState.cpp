// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/State/UPACSkillState.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "Data/DataAttributeSet/BossDataSet/UPBossSkillAttributeSet.h"

// Sets default values for this component's properties
UUPACSkillState::UUPACSkillState()
{

}

void UUPACSkillState::InitSkillState(AActor* Owner, TSubclassOf<UUPBossSkillAttributeSet> AttributeSetType)
{
	AttributeSet = NewObject<UUPBossSkillAttributeSet>(Owner, AttributeSetType);
	if (AttributeSet != nullptr && Owner)
	{
		AttributeSet->Rename(*AttributeSetType->GetName(), Owner);
	}
}

void UUPACSkillState::PostInitialize(int32 CurPhaseNumber)
{
	if (AttributeSet)
	{
		UE_LOG(LogTemp,Error, TEXT("1111"));
		AttributeSet->InitAttributeSet(CurPhaseNumber);
	}
}
