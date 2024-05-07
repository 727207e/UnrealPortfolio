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
public:
	virtual void SetAbilitySystemComponent(AActor* InOwner) override;
	void OnMpChanged(const FOnAttributeChangeData& ChangeData);
	void OnMaxMpChanged(const FOnAttributeChangeData& ChangeData);
	virtual void UpdateProgressBar() override;
};
