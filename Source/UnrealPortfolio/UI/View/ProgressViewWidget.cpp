// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/View/ProgressViewWidget.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

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

// void UProgressViewWidget::OnHealthChanged(const FOnAttributeChangeData& ChangeData)
// {
// 	CurrentRatio = ChangeData.NewValue;
// 	UpdateProgressBar();
// }
//
// void UProgressViewWidget::OnMaxHealthChanged(const FOnAttributeChangeData& ChangeData)
// {
// 	
// }


void UProgressViewWidget::UpdateProgressBar()
{
	if (PbBar)
	{
		PbBar->SetPercent(CurrentRatio / MaxRatio);
	}
    
	if (Text_Stat)
	{
		Text_Stat->SetText(FText::FromString(FString::Printf(TEXT("%.0f/%0.f"), CurrentRatio, MaxRatio)));
	}
}
