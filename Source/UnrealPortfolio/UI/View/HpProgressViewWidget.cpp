// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/View/HpProgressViewWidget.h"

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Kismet/KismetSystemLibrary.h"

void UHpProgressViewWidget::SetAbilitySystemComponent(AActor* InOwner)
{
	Super::SetAbilitySystemComponent(InOwner);

	if (ASC)
	{
		ASC->GetGameplayAttributeValueChangeDelegate(UUPMainCharacterAttributeSet::GetHpAttribute()).AddUObject(this, &UHpProgressViewWidget::OnHpChanged);
		ASC->GetGameplayAttributeValueChangeDelegate(UUPMainCharacterAttributeSet::GetMaxHpAttribute()).AddUObject(this, &UHpProgressViewWidget::OnMaxHpChanged);
	}

	if (const UEntityAttributeSet* CurrentAttributeSet = ASC->GetSet<UEntityAttributeSet>())
	{
		CurrentRatio = CurrentAttributeSet->GetHp();
		MaxRatio = CurrentAttributeSet->GetMaxHp();
		UpdateProgressBar();
	}
}
void UHpProgressViewWidget::OnHpChanged(const FOnAttributeChangeData& ChangeData)
{
	CurrentRatio = ChangeData.NewValue;
	UpdateProgressBar();
}

void UHpProgressViewWidget::OnMaxHpChanged(const FOnAttributeChangeData& ChangeData)
{
	MaxRatio = ChangeData.NewValue;
	UpdateProgressBar();
}

void UHpProgressViewWidget::StartTimer()
{
	GetWorld()->GetTimerManager().SetTimer(ProgressAnimTimer, this, &UHpProgressViewWidget::DecreaseProgressBar, 0.0333f, true);
}

void UHpProgressViewWidget::UpdateProgressBar()
{
	Super::UpdateProgressBar();
	if (TextStat)
	{
		TextStat->SetText(FText::FromString(FString::Printf(TEXT("%.0f/%0.f"), CurrentRatio, MaxRatio)));
	}
	StartTimmer();
}


void UHpProgressViewWidget::DecreaseProgressBar()
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
