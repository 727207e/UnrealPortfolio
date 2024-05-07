// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/UPEnemyCharacter.h"
#include "UPBossCharacter.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPORTFOLIO_API AUPBossCharacter : public AUPEnemyCharacter
{
	GENERATED_BODY()
	
public:
	AUPBossCharacter();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TObjectPtr<class UAnimMontage> GroggyMontage;

	virtual void BeginPlay() override;
	virtual void CounterAttackHit();
};
