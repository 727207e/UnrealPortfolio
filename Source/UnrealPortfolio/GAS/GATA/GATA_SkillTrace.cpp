// Fill out your copyright notice in the Description page of Project Settings.


#include "GATA_SkillTrace.h"
#include "Components/DecalComponent.h"
#include "GAS/GATA/GATA_Trace.h"

AGATA_SkillTrace::AGATA_SkillTrace()
{
	bIsDrawDecal = false;
}

void AGATA_SkillTrace::ConfirmTargetingAndContinue()
{
	if (bIsDrawDecal)
	{
		DrawDecal();
	}
	else
	{
		Super::ConfirmTargetingAndContinue();
	}
}

void AGATA_SkillTrace::DrawDecal()
{
	UE_LOG(LogTemp, Error, TEXT("This Skill Has not Decal Logic"));
	return;
}
