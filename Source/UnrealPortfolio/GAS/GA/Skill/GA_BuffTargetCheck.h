// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Character/UPMainCharacter.h"
#include "UI/View/SlotViewWidget.h"
#include "GA_BuffTargetCheck.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPORTFOLIO_API UGA_BuffTargetCheck : public UGameplayAbility
{

	UGA_BuffTargetCheck();
	
	GENERATED_BODY()
	int32 TargetSkillAbilityIndex;
	UPROPERTY()
	TObjectPtr<USlotViewWidget> BuffSlot;
protected:
	virtual auto ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
							 const FGameplayAbilityActivationInfo ActivationInfo,
							 const FGameplayEventData* TriggerEventData) -> void override;
	virtual auto CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
							   const FGameplayAbilityActivationInfo ActivationInfo,
							   bool bReplicateCancelAbility) -> void override;

	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	                        const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility,
	                        bool bWasCancelled) override;
	UFUNCTION()
	void OnBuffEnd();
	UPROPERTY(EditAnywhere, Category = "GAS")
	TSubclassOf<class UGameplayEffect> AttackDamageEffect;
	UFUNCTION()
	virtual void OnTraceResultCallback(const FGameplayAbilityTargetDataHandle& TargetDataHandle);
	UClass* CurrentTA;
	FGameplayAbilityTargetDataHandle TargetData;
	int32 BuffCount;
	
	//함수를 클라이언트에서 호출되지만
	//서버에서 실행되는 rpc입니다.
	UFUNCTION(Server, Unreliable)
	void Server_SendMessageBuffSlot();
	
	//함수를 서버에서 호출되지만
	//클라이언트에서 실행되는 rpc입니다.
	

};
