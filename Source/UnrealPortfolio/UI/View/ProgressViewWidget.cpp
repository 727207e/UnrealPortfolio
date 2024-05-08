// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/View/ProgressViewWidget.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Components/ProgressBar.h"
#include "Data/DataTable/Widget/ProgressWidgetModelData.h"

void UProgressViewWidget::SetAbilitySystemComponent(AActor* InOwner)
{
	if (IsValid(InOwner))
	{
		ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(InOwner);
	}
}

UAbilitySystemComponent* UProgressViewWidget::GetAbilitySystemComponent() const
{
	return  ASC;
}

void UProgressViewWidget::SetData(const FProgressWidgetModelData& ModelData)
{
	PbBar->SetFillColorAndOpacity(ModelData.ProgressFillColor);
	Duration = ModelData.Duration;
}


void UProgressViewWidget::UpdateProgressBar()
{
	
}
