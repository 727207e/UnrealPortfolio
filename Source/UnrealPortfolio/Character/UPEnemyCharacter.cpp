// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/UPEnemyCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"


AUPEnemyCharacter::AUPEnemyCharacter()
{
}

void AUPEnemyCharacter::SetDead()
{
	Super::SetDead();
}

void AUPEnemyCharacter::MeshSetSimulatePhysics(USkeletalMeshComponent* targetMesh, UCapsuleComponent* targetCapsule)
{
	targetMesh->SetCollisionProfileName(TEXT("PhysicsActor"));
	targetMesh->SetAnimInstanceClass(nullptr);
	targetMesh->SetSimulatePhysics(true);

	if (targetCapsule)
	{
		targetCapsule->SetGenerateOverlapEvents(false);
	}
}