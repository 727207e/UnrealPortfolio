// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAS/GA/Skill/GA_BossStruggleSkill.h"
#include "GA_BossStruggleSkillFlyDN.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPORTFOLIO_API UGA_BossStruggleSkillFlyDN : public UGA_BossStruggleSkill
{
	GENERATED_BODY()
	
public :
	UGA_BossStruggleSkillFlyDN();

protected :
	virtual void SettingBossDummy() override;

private :
	UFUNCTION()
	void FlyingSetDown();

	float ZOffset = 0;
	float ElapsedTime = 0;
	float LerpDuration = 0;
	FVector StartPosition;
	FVector EndPosition;

	FTimerHandle FlyDownTimerHandle;
};
