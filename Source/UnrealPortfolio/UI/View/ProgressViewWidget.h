// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "Data/DataTable/Widget/ProgressWidgetModelData.h"
#include "Data/DataTable/Widget/SlotWidgetModelData.h"
#include "GAS/Attribute/PlayerDataSet/UPMainCharacterAttributeSet.h"
#include "UI/UPUserWidget.h"
#include "ProgressViewWidget.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPORTFOLIO_API UProgressViewWidget : public UUPUserWidget ,public IAbilitySystemInterface
{
	GENERATED_BODY()
public:
	
	virtual void SetAbilitySystemComponent(AActor* InOwner);
	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	void SetData(const FProgressWidgetModelData& ModelData);

protected:
	UPROPERTY(EditAnywhere, Category = GAS)
	TObjectPtr<class UAbilitySystemComponent> ASC;

	virtual void UpdateProgressBar();
	
protected:
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UProgressBar> PbBar;
    
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> TextStat;

	float CurrentRatio = 0.0f;
	float MaxRatio = 0.1f;
	float Duration;

	
};
