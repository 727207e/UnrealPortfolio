// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTargetActor.h"
#include "GATA_Trace.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPORTFOLIO_API AGATA_Trace : public AGameplayAbilityTargetActor
{
	GENERATED_BODY()

public:
	AGATA_Trace();
    
	virtual void StartTargeting(UGameplayAbility* Ability) override;
    
	virtual void ConfirmTargetingAndContinue() override;
	void SetShowDebug(bool InShowDebug) { bShowDebug = InShowDebug; }
    
protected:
	//정보들을 반환 왜 프로텍트지
	virtual FGameplayAbilityTargetDataHandle MakeTargetData() const;
    
	bool bShowDebug = false;

	
};

