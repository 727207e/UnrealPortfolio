// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/View/MpProgressViewWidget.h"

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UMpProgressViewWidget::SetAbilitySystemComponent(AActor* InOwner)
{
	Super::SetAbilitySystemComponent(InOwner);
	if (ASC)
	{
		ASC->GetGameplayAttributeValueChangeDelegate(UUPMainCharacterAttributeSet::GetMpAttribute()).AddUObject(this, &UMpProgressViewWidget::OnMpChanged);
		ASC->GetGameplayAttributeValueChangeDelegate(UUPMainCharacterAttributeSet::GetMaxMpAttribute()).AddUObject(this, &UMpProgressViewWidget::OnMaxMpChanged);
	}

	if (const UUPMainCharacterAttributeSet* CurrentAttributeSet = ASC->GetSet<UUPMainCharacterAttributeSet>())
	{
		CurrentRatio = CurrentAttributeSet->GetMp();
		MaxRatio = CurrentAttributeSet->GetMaxMp();
		UpdateProgressBar();
	}
	
}

void UMpProgressViewWidget::OnMpChanged(const FOnAttributeChangeData& ChangeData)
{
	CurrentRatio = ChangeData.NewValue;
	UpdateProgressBar();
}

void UMpProgressViewWidget::OnMaxMpChanged(const FOnAttributeChangeData& ChangeData)
{
	MaxRatio = ChangeData.NewValue;
	UpdateProgressBar();
}

void UMpProgressViewWidget::UpdateProgressBar()
{
	Super::UpdateProgressBar();
	if (PbBar)
	{
		PbBar->SetPercent(CurrentRatio / MaxRatio);
	}
    
	if (TextStat)
	{
		TextStat->SetText(FText::FromString(FString::Printf(TEXT("%.0f/%0.f"), CurrentRatio, MaxRatio)));
	}
}
