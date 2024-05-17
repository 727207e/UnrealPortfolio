// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAS/GA/Skill/GA_BossStruggleSkill.h"
#include "GA_BossStruggleSkillFlyUp.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPORTFOLIO_API UGA_BossStruggleSkillFlyUp : public UGA_BossStruggleSkill
{
	GENERATED_BODY()
	
public :
	UGA_BossStruggleSkillFlyUp();

protected:
	virtual void SettingBossDummy() override;

private:
	UFUNCTION()
	void FlyingSetUp();

	float ZOffset = 0;
	float ElapsedTime = 0;
	float LerpDuration = 0;
	float StartTimerDelay = 0;
	FVector StartPosition;
	FVector EndPosition;

	FTimerHandle FlyUpTimerHandle;
};
