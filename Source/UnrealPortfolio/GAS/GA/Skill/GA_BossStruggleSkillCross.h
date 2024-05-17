// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAS/GA/Skill/GA_BossStruggleSkill.h"
#include "GA_BossStruggleSkillCross.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPORTFOLIO_API UGA_BossStruggleSkillCross : public UGA_BossStruggleSkill
{
	GENERATED_BODY()
	
public : 
	UGA_BossStruggleSkillCross();

protected :
	virtual void SettingBossDummy() override;

private :
	UFUNCTION()
	void BossFlyForward();

};
