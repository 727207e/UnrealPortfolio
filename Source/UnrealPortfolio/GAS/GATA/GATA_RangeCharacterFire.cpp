// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/GATA/GATA_RangeCharacterFire.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

AGATA_RangeCharacterFire::AGATA_RangeCharacterFire()
{
	SocketName = "Hand_r";

	ProjectTileMovement->InitialSpeed = 1000;
	ProjectTileMovement->MaxSpeed = 1000;
	ProjectTileMovement->bShouldBounce = true;
	ProjectTileMovement->ProjectileGravityScale = 0;
	ProjectTileMovement->Velocity = FVector(1000, 0, 0);
}
