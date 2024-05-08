// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/View/ProgressViewWidget.h"
#include "MpProgressViewWidget.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPORTFOLIO_API UMpProgressViewWidget : public UProgressViewWidget
{
	GENERATED_BODY()
private:
	FTimerHandle ProgressAnimTimer;
public:
	virtual void SetAbilitySystemComponent(AActor* InOwner) override;
	void OnMpChanged(const FOnAttributeChangeData& ChangeData);
	void OnMaxMpChanged(const FOnAttributeChangeData& ChangeData);
	void StartTimer();
	float DelTime;
	virtual void UpdateProgressBar() override;
	float CurrentProgress;
	void DecreaseProgressBar();
};
