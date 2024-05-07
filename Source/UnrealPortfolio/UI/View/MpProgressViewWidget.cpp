// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/View/MpProgressViewWidget.h"

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Kismet/KismetSystemLibrary.h"

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

void UMpProgressViewWidget::StartTimer()
{
	GetWorld()->GetTimerManager().SetTimer(ProgressAnimTimer, this, &UMpProgressViewWidget::DecreaseProgressBar, 0.0333f, true);
}

void UMpProgressViewWidget::UpdateProgressBar()
{
	Super::UpdateProgressBar();
	if (TextStat)
	{
		TextStat->SetText(FText::FromString(FString::Printf(TEXT("%.0f/%0.f"), CurrentRatio, MaxRatio)));
	}
	StartTimer();
}

void UMpProgressViewWidget::DecreaseProgressBar()
{
	if(ProgressAnimTimer.IsValid())
	{
		DelTime += UKismetSystemLibrary::K2_GetTimerElapsedTimeHandle(GetWorld(),ProgressAnimTimer);
		const float Alpha = DelTime / Duration;
		CurrentProgress = FMath::Lerp(CurrentProgress, (CurrentRatio / MaxRatio),Alpha);
		if (PbBar)
		{
			PbBar->SetPercent(CurrentProgress);
		}
	}

	if(DelTime >= Duration)
	{
		DelTime = 0.0f;
		GetWorld()->GetTimerManager().ClearTimer(ProgressAnimTimer);
		PbBar->SetPercent(CurrentRatio / MaxRatio);
	}
}
