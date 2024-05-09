// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/UPEnemyCharacter.h"
#include "Interface/BossInterface.h"
#include "UPBossCharacter.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPORTFOLIO_API AUPBossCharacter : public AUPEnemyCharacter ,public IBossInterface
{
	GENERATED_BODY()
	
public:
	AUPBossCharacter();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TObjectPtr<class UAnimMontage> GroggyMontage;

	virtual void BeginPlay() override;
	virtual void CounterAttackHit();

public :
	UFUNCTION()
	void MontageEndEvent(UAnimMontage* Montage, bool bInterrupted);

	UPROPERTY(EditAnywhere)
	float CounterResetDelayTime;

	virtual void OnDead() override;
	virtual  UAbilitySystemComponent* GetBossAbilitySystemComponent() override; 
};
