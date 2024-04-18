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
	/** Unreal Life **/
	/** Unreal Life **/
protected:
	virtual void PostInitializeComponents() override;
	virtual void PossessedBy(AController* NewController) override;

	
	/** Game Ability System **/
	/** Game Ability System **/

	UPROPERTY()
	TObjectPtr<class UAbilitySystemComponent> ASC;

	UPROPERTY(EditAnywhere, Category = GAS)
	TArray<TSubclassOf<class UGameplayAbility>> StartAbilities;
	
	UPROPERTY(EditAnywhere, Category = GAS)
	TMap<int32, TSubclassOf<class UGameplayAbility>> StartInputAbilities;

private:
	void SetupASC_EnemyCharacter();
	void SetupASC_Player();
	
public:
	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	
	/** Character Animation **/
	/** Character Animation **/
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TObjectPtr<class UUPComboActionData> ComboActionData;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TObjectPtr<class UAnimMontage> ComboActionMontage;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TObjectPtr<class  UAnimMontage> DeadMontage;
	
	virtual void SetDead() override;
	virtual UAnimMontage* GetComboActionMontage() override;
	FORCEINLINE virtual UUPComboActionData* GetComboActionData() const { return ComboActionData; }
};