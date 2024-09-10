// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/UPEnemyCharacter.h"
#include "UPMeleeEnemyCharacter.generated.h"

class USkeletalMeshComponent;
/**
 * 
 */
UCLASS()
class UNREALPORTFOLIO_API AUPMeleeEnemyCharacter : public AUPEnemyCharacter
{
	GENERATED_BODY()
	
public :
	AUPMeleeEnemyCharacter();

	virtual void OnDead() override;

protected :
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh)
	TObjectPtr<USkeletalMeshComponent> BeltMesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh)
	TObjectPtr<USkeletalMeshComponent> TrousersMesh;
};