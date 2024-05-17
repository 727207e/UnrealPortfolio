// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/GA/Skill/GA_BossStruggleSkillCross.h"
#include "Game/BossManager.h"

UGA_BossStruggleSkillCross::UGA_BossStruggleSkillCross()
{
}

void UGA_BossStruggleSkillCross::SettingBossDummy()
{
	BossDummy->SetActorTransform(BossManager->GetRandomAroundTransform());

	FTimerHandle FlyForwardTimer;
	GetWorld()->GetTimerManager().SetTimer(FlyForwardTimer, this, &UGA_BossStruggleSkillCross::BossFlyForward, GetWorld()->DeltaTimeSeconds, true);
}

void UGA_BossStruggleSkillCross::BossFlyForward()
{
	FVector NewLocation = BossDummy->GetActorLocation() + (BossDummy->GetActorForwardVector() * GetWorld()->DeltaTimeSeconds * Speed);
	BossDummy->SetActorLocation(NewLocation);
}
