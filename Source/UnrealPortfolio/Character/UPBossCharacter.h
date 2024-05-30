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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Entity)
	TSubclassOf<class UUPACSkillState> BossSkillStateForm;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Entity)
	TArray<TSubclassOf<class UUPBossSkillAttributeSet>> BossSkillAttributeSetTypeArray;
	UPROPERTY()
	TArray<TObjectPtr<class UUPACSkillState>> BossSkillStateArray;

	virtual void PreInitializeComponents() override;
	virtual void PostInitializeComponents() override;
	virtual void SkillEndCallBack() override;
	virtual void CounterAttackHit();
	
	void UpdatePhaseNumber(int32 PhaseNumber);

public :
	UFUNCTION()
	void MontageEndEvent(UAnimMontage* Montage, bool bInterrupted);

	UPROPERTY(EditAnywhere)
	float CounterResetDelayTime;

	UPROPERTY(EditAnywhere)
	int32 CurPhaseNumber;

	virtual void OnDead() override;
	virtual  UAbilitySystemComponent* GetBossAbilitySystemComponent() override; 
};
