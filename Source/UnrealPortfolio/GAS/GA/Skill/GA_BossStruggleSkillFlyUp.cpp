// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/GA/Skill/GA_BossStruggleSkillFlyUp.h"
#include "Character/UPStrugglingBoss.h"
#include "GameFramework/Character.h"
#include "Game/BossManager.h"

UGA_BossStruggleSkillFlyUp::UGA_BossStruggleSkillFlyUp()
{
	ZOffset = 3000;
	LerpDuration = 1.3f;
	StartTimerDelay = 1.3f;
}

void UGA_BossStruggleSkillFlyUp::SettingBossDummy()
{
	AttackSpeed = 0.3f;

	StartPosition = BossDummy->GetActorLocation();
	EndPosition = BossDummy->GetActorLocation() + FVector(0.0f, 0.0f, ZOffset);

	GetWorld()->GetTimerManager().SetTimer(FlyUpTimerHandle, this, &UGA_BossStruggleSkillFlyUp::FlyingSetUp, GetWorld()->DeltaTimeSeconds, true, StartTimerDelay);
}

void UGA_BossStruggleSkillFlyUp::FlyingSetUp()
{
	ElapsedTime += GetWorld()->DeltaTimeSeconds;

	float LerpAlpha = FMath::Clamp(ElapsedTime / LerpDuration, 0.0f, 1.0f);
	FVector NewLocation = FMath::Lerp(StartPosition, EndPosition, LerpAlpha);

	BossDummy->SetActorLocation(NewLocation);

	if (LerpAlpha >= 1.0f)
	{
		GetWorld()->GetTimerManager().ClearTimer(FlyUpTimerHandle);
	}
}
