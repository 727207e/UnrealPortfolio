// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/UPBattleBaseCharacter.h"
#include "UPEnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPORTFOLIO_API AUPEnemyCharacter : public AUPBattleBaseCharacter
{
	GENERATED_BODY()
	
public :
	AUPEnemyCharacter();

	virtual void SetDead() override;

	virtual  void PostInitializeComponents() override;
	
};
