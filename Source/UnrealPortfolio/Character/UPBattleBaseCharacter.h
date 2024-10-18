// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/UPCharacter.h"
#include "AbilitySystemInterface.h"
#include "Interface/AbilitySystemGetInterface.h"
#include "Interface/AttackableCharacterInterface.h"
#include "AbilitySystemComponent.h"
#include "UPBattleBaseCharacter.generated.h"

/**
 * 
 */

DECLARE_MULTICAST_DELEGATE(FOnEndAttackDelegate);
DECLARE_MULTICAST_DELEGATE(FOnEndSkillDelegate);
DECLARE_MULTICAST_DELEGATE(FOnHitDelegate);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnAttackEffectEvent, FGameplayTag);

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
	
	/** When use to Host Character Initialize **/
	virtual void PossessedBy(AController* NewController) override;
	/** When use to Client Character Initialize **/
	virtual void OnRep_PlayerState() override;
	
	/** Game Ability System **/
	/** Game Ability System **/
	
	UPROPERTY()
	TObjectPtr<class UAbilitySystemComponent> ASC;

	UPROPERTY(EditAnywhere, Category = GAS)
	TArray<TSubclassOf<class UGameplayAbility>> StartAbilities;
	
	UPROPERTY(EditAnywhere, Category = GAS)
	TMap<int32, TSubclassOf<class UGameplayAbility>> StartInputAbilities;

	UPROPERTY()
	TArray<FGameplayAbilitySpec> UsingGAArray;

protected:
	virtual void SetupASCHostPlayer(AActor* InOwnerActor);
	virtual void SetupASCClientPlayer();
	
public:
	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	TArray<FGameplayAbilitySpec> GetUsingGas(int32 GameplayAbilityInputId);

	/** Character Animation **/
	/** Character Animation **/
	
protected:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TObjectPtr<class UUPComboActionData> ComboActionData;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TObjectPtr<class UAnimMontage> ComboActionMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TObjectPtr<class UAnimMontage> HitMontage;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TObjectPtr<class  UAnimMontage> DeadMontage;
	
	virtual UAnimMontage* GetComboActionMontage() override;
	FORCEINLINE virtual UUPComboActionData* GetComboActionData() const { return ComboActionData; }

	UFUNCTION(BlueprintCallable , Category = GAS)
	virtual void CallGAS(int32 GameplayAbilityInputId);
	virtual void Hit(FVector TargetLocation, TObjectPtr<class AGameplayEventDataRequest> ActionData) override;
	virtual void PlayHitAnimation() override;
	
	void Knockback(TObjectPtr<class AGameplayEventDataRequest> ActionData);

	FTimerHandle AttackDelay;
	void SetAttackDelay(float DelayTime);

public :
	bool bCanAttack;
	virtual void AttackEndCallBack() override;
	void AddAttackEndCallBack(const FOnEndAttackDelegate& OnEndAttack);	//���� �Ǵ��� Ȯ���غ���.
	virtual void SkillEndCallBack() override;
	virtual void NormalAttack();
	virtual void OnSkill(int32 SkillNumber);

public :
	FOnEndAttackDelegate OnEndAttackDelegate;
	FOnEndSkillDelegate OnEndSkillDelegate;
	FOnHitDelegate OnHitDelegate;
	FOnAttackEffectEvent OnAttackEffect;

	void AddOnHitDelegate(FOnHitDelegate& Delegate);
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UEntityAttributeSet> AttributeSet;

	virtual void OnDead() override;
	
};