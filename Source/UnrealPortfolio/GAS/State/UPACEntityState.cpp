// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/State/UPACEntityState.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "Data/DataAttributeSet/EntityAttributeSet.h"

// Sets default values for this component's properties
UUPACEntityState::UUPACEntityState()
{
	ASC = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("ASC"));
}

void UUPACEntityState::BeginPlay()
{
	AttributeSet->GetDefaultObject<UEntityAttributeSet>()->InitAttributeSet();
}

//Delete This!
void UUPACEntityState::TestMethod()
{
	//AttributeSet->
}
