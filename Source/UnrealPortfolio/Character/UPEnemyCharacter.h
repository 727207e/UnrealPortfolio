// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/UPBattleBaseCharacter.h"
#include "UPEnemyCharacter.generated.h"

/**
 * 
 */

DECLARE_DELEGATE(FOnEndAnimDelegate);

UCLASS()
class UNREALPORTFOLIO_API AUPEnemyCharacter : public AUPBattleBaseCharacter
{
	GENERATED_BODY()
	
public :
	AUPEnemyCharacter();

	virtual void PreInitializeComponents() override;
	virtual void PostInitializeComponents() override;

protected :
	void MeshSetSimulatePhysics(class USkeletalMeshComponent* targetMesh, class UCapsuleComponent* targetCapsule = nullptr);
	virtual void SetupASCHostPlayer(AActor* InOwnerActor) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Entity)
	TSubclassOf<class UUPACEntityState> EnemyEntityStateType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Entity)
	TObjectPtr<class UUPACEntityState> EnemyEntityState;

	virtual void OnDead() override;
	
public :
	virtual void NormalAttack() override;
	virtual void OnSkill(int32 SkillNumber) override;
	FGameplayAbilitySpec FindTarget();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TObjectPtr<class UAnimMontage> FindTargetMontage;

	FOnEndAnimDelegate OnEndAnimDelegate;
	void SetDelegate(const FOnEndAnimDelegate& OnEndAnim);

	void OnFindTargetEnd();

protected :
	int32 AttackDelayTime;
};
