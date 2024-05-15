// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAS/GA/Skill/GA_BossSkill.h"
#include "Character/UPEnemyCharacter.h"
#include "GA_BossEnemySpawnSkill.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPORTFOLIO_API UGA_BossEnemySpawnSkill : public UGA_BossSkill
{
	GENERATED_BODY()

public :
	UGA_BossEnemySpawnSkill();

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UNiagaraSystem> SpawnVisual;

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<AUPEnemyCharacter>> EnemyArray;

protected :
	virtual auto ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		const FGameplayEventData* TriggerEventData) -> void override;

	TArray<FVector> GetRandomRadiusPosition();

private :
	float SpawnDelay = 0.f;
	float SearchingRadius = 0;

	void SpawnEnemies();
	void SettingTarget(ACharacter* TargetEnemy);
};
