// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAS/GATA/GATA_RangeEnemeyFire.h"
#include "GATA_BossRangeMultiFire.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPORTFOLIO_API AGATA_BossRangeMultiFire : public AGATA_RangeEnemeyFire
{
	GENERATED_BODY()
	
public :
	AGATA_BossRangeMultiFire();

protected:
	void OnProjectileFindTarget(const FGameplayAbilityTargetDataHandle& DataHandle);

public:
	virtual void ConfirmTargetingAndContinue() override;

private :
	void InitializeSphere();
};
