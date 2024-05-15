// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/GATA/GATA_BossStruggleSquare.h"
#include "Components/DecalComponent.h"
#include "GameFramework/Actor.h"

AGATA_BossStruggleSquare::AGATA_BossStruggleSquare()
{
	bIsDrawDecal = true;
}

void AGATA_BossStruggleSquare::GetAttributeSetting()
{
	BoxSizeX = BoxSizeXValue;
	BoxSizeY = BoxSizeYValue;
}

void AGATA_BossStruggleSquare::DrawDecal()
{
	Super::DrawDecal();

	this->AttachToActor(SourceActor, FAttachmentTransformRules::KeepWorldTransform);
}
