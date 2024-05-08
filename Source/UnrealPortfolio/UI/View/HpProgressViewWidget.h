// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/View/ProgressViewWidget.h"
#include "HpProgressViewWidget.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPORTFOLIO_API UHpProgressViewWidget : public UProgressViewWidget
{
	GENERATED_BODY()
private:
	FTimerHandle ProgressAnimTimer;
public:
	virtual void SetAbilitySystemComponent(AActor* InOwner) override;
	void OnHpChanged(const FOnAttributeChangeData& ChangeData);
	void OnMaxHpChanged(const FOnAttributeChangeData& ChangeData);
	void StartTimer();
	float DelTime;
	virtual void UpdateProgressBar() override;
	float CurrentProgress;
	void DecreaseProgressBar();
};


