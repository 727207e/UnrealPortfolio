// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/UPEnemyCharacter.h"
#include "UPRangedEnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPORTFOLIO_API AUPRangedEnemyCharacter : public AUPEnemyCharacter
{
	GENERATED_BODY()
	
public :
	AUPRangedEnemyCharacter();

	virtual void OnDead() override;

};
