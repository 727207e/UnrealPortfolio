// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Character/UPBattleBaseCharacter.h"
#include "GA_CheckGameOver.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPORTFOLIO_API UGA_CheckGameOver : public UGameplayAbility
{
	GENERATED_BODY()
	UGA_CheckGameOver();
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
public:
	UPROPERTY(EditAnywhere, Category= GAS)
	FGameplayTag DeadTag;
	UPROPERTY(EditAnywhere, Category= GAS)
	FGameplayTag BossDeadTag;
	
private:
	UPROPERTY();
	int PlayerMaxCount;
	int PlayerCurrentDeadCount;
	
	UFUNCTION()
	void CheckDeadTargetCharacter(TSubclassOf<AUPBattleBaseCharacter> CharacterClassType);
	UFUNCTION()
	void OnPlayerIsDead(const FGameplayTag TargetTag, int32 NewCount);
	UFUNCTION()
	void BossIsDead(const FGameplayTag TargetTag, int32 NewCount);
};
