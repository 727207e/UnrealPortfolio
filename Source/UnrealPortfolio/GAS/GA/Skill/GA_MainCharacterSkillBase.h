// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAS/GA/Skill/GA_SkillBase.h"
#include "UI/UPMainHudWidget.h"
#include "GA_MainCharacterSkillBase.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPORTFOLIO_API UGA_MainCharacterSkillBase : public UGA_SkillBase
{
	GENERATED_BODY()
protected:
	UGA_MainCharacterSkillBase();
protected:
	void SetData();
protected:
	virtual auto ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
							 const FGameplayAbilityActivationInfo ActivationInfo,
							 const FGameplayEventData* TriggerEventData) -> void override;
	

	/** Destroys instanced-per-execution abilities. Instance-per-actor abilities should 'reset'. Any active ability state tasks receive the 'OnAbilityStateInterrupted' event. Non instance abilities - what can we do? */
	virtual auto CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
							   const FGameplayAbilityActivationInfo ActivationInfo,
							   bool bReplicateCancelAbility) -> void override;

	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

	virtual void InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) override;
	virtual void SetSlotWidget(USlotViewWidget* TargetSlotWidget);
	virtual void OnCompleteCallback() override;
	
protected:
	UPROPERTY(BlueprintReadOnly , Category = GAS);
	int32 Cooldown;
	UPROPERTY(BlueprintReadOnly , Category = GAS);
	int32 MagicPoints;
	UPROPERTY(BlueprintReadOnly , Category = GAS);
	int32 TargetSkillAbilityIndex;
	UPROPERTY(EditAnywhere , Category = GAS);
	TSubclassOf<UGameplayEffect> UseMpEffect;
	UPROPERTY(EditAnywhere , Category = GAS);
	bool bCantLookAtMouseAbility;
	TObjectPtr<USlotViewWidget> SkillSlotWidget;
	void UseMp(const FGameplayAbilityActivationInfo ActivationInfo);

};
