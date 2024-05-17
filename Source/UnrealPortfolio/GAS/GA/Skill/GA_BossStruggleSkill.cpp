// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/GA/Skill/GA_BossStruggleSkill.h"
#include "Character/UPStrugglingBoss.h"
#include "Game/BossManager.h"
#include "Game/UPGameInstance.h"

UGA_BossStruggleSkill::UGA_BossStruggleSkill()
{
	Speed = 5000.0f;
}

void UGA_BossStruggleSkill::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (!IsBossDummySettingDone())
	{
		return;
	}
	BossDummy = Cast<AUPStrugglingBoss>(ActorInfo->AvatarActor);

	SettingBossDummy();
}

void UGA_BossStruggleSkill::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	BossDummy->PlayNextPatern();

	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}


bool UGA_BossStruggleSkill::IsBossDummySettingDone()
{
	UUPGameInstance* UpGameInstance = Cast<UUPGameInstance>(GetWorld()->GetGameInstance());
	if (nullptr == UpGameInstance)
	{
		UE_LOG(LogTemp, Error, TEXT("BossTruggleSkill : Can't Find GameInstance"));
		return false;
	}

	BossManager = UpGameInstance->GetBossManager();
	if (nullptr == BossManager)
	{
		UE_LOG(LogTemp, Error, TEXT("BossTruggleSkill : Can't Find BossManager"));
		return false;
	}

	return true;
}