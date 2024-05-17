// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/GA/Skill/GA_BossStruggleSkillFlyDN.h"
#include "Character/UPStrugglingBoss.h"
#include "Game/BossManager.h"

UGA_BossStruggleSkillFlyDN::UGA_BossStruggleSkillFlyDN()
{
	ZOffset = 3000;
	LerpDuration = 1.3;
}

void UGA_BossStruggleSkillFlyDN::SettingBossDummy()
{
	AActor* DestinationActor = BossManager->GenPosition;

	FTransform TargetTransform = DestinationActor->GetActorTransform();
	TargetTransform.SetLocation(TargetTransform.GetLocation() + FVector(0.0f, 0.0f, ZOffset));
	BossDummy->SetActorTransform(TargetTransform);

	StartPosition = BossDummy->GetActorLocation();
	EndPosition = DestinationActor->GetActorLocation();

	GetWorld()->GetTimerManager().SetTimer(FlyDownTimerHandle, this, &UGA_BossStruggleSkillFlyDN::FlyingSetDown, GetWorld()->DeltaTimeSeconds, true);
}

void UGA_BossStruggleSkillFlyDN::FlyingSetDown()
{
	ElapsedTime += GetWorld()->DeltaTimeSeconds;

	float LerpAlpha = FMath::Clamp(ElapsedTime / LerpDuration, 0.0f, 1.0f);
	FVector NewLocation = FMath::Lerp(StartPosition, EndPosition, LerpAlpha);

	BossDummy->SetActorLocation(NewLocation);

	if (LerpAlpha >= 1.0f)
	{
		GetWorld()->GetTimerManager().ClearTimer(FlyDownTimerHandle);
	}
}
