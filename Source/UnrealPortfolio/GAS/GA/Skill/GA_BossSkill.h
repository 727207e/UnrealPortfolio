// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAS/GA/Skill/GA_SkillBase.h"
#include "GA_BossSkill.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPORTFOLIO_API UGA_BossSkill : public UGA_SkillBase
{
	GENERATED_BODY()

public :
	UGA_BossSkill();
	
public :
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FName> SkillSectionList;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 SkillNumber;

protected:
	virtual auto ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		const FGameplayEventData* TriggerEventData) -> void override;
	
	virtual void OnCompleteCallback() override;
	class UAbilitySystemComponent* SourceASC;
	const class UUPBossSkillAttributeSet* SourceAttribute;

private :
	void PlayNextMontage();
	int32 IndexNumber;
};
