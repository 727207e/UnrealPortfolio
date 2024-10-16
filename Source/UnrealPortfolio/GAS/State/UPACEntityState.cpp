// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/State/UPACEntityState.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "GAS/Attribute/EntityAttributeSet.h"

// Sets default values for this component's properties
UUPACEntityState::UUPACEntityState()
{

}

void UUPACEntityState::InitEntityState(AActor* Owner)
{
	ASC = NewObject<UAbilitySystemComponent>(Owner, UAbilitySystemComponent::StaticClass(), TEXT("ASC"));
	
	Owner->AddOwnedComponent(ASC);
	ASC->RegisterComponent();
	ASC->SetIsReplicated(true);
	ASC->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	if (AttributeSetType)
	{
		AttributeSet = NewObject<UEntityAttributeSet>(Owner, AttributeSetType);
		if (AttributeSet != nullptr)
		{
			AttributeSet->Rename(TEXT("Attribute"), Owner);
		}
	}
}

void UUPACEntityState::PostInitialize()
{
	if (AttributeSetType)
	{
		AttributeSet->InitAttributeSet();
	}
}