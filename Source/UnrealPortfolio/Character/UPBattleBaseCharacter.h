// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/UPCharacter.h"
#include "AbilitySystemInterface.h"
#include "Interface/AbilitySystemGetInterface.h"
#include "Interface/AttackableCharacterInterface.h"
#include "UPBattleBaseCharacter.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPORTFOLIO_API AUPBattleBaseCharacter : public AUPCharacter
	, public IAbilitySystemInterface
	, public IAbilitySystemGetInterface
	, public IAttackableCharacterInterface
{
	GENERATED_BODY()
	
public :
	AUPBattleBaseCharacter();
	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:
	virtual void PostInitializeComponents() override;
	virtual void PossessedBy(AController* NewController) override;

private:
	void SetupASC_EnemyCharacter();
	void SetupASC_Player();
	
public :
	virtual void SetDead() override;
	/** GAS **/
	UPROPERTY()
	TObjectPtr<class UAbilitySystemComponent> ASC;

//Battle Animation
protected:
	TObjectPtr<class UUPComboActionData> ComboActionData;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TObjectPtr<class UAnimMontage> ComboActionMontage;
	FORCEINLINE virtual UUPComboActionData* GetComboActionData() const { return ComboActionData; }
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TObjectPtr<class  UAnimMontage> DeadMontage;
protected:
	UPROPERTY(EditAnywhere, Category = GAS)
	TArray<TSubclassOf<class UGameplayAbility>> StartAbilities;
	
	UPROPERTY(EditAnywhere, Category = GAS)
	TMap<int32, TSubclassOf<class UGameplayAbility>> StartInputAbilities;

	
	
	
protected:
	virtual UAnimMontage* GetComboActionMontage() override;
};