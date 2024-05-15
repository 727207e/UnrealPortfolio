// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/GA/Skill/GA_BossStruggleSkillCross.h"
#include "Game/BossManager.h"
#include "Game/UPGameInstance.h"

UGA_BossStruggleSkillCross::UGA_BossStruggleSkillCross()
{
	Speed = 5000.0f;
}

void UGA_BossStruggleSkillCross::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	UUPGameInstance* UpGameInstance = Cast<UUPGameInstance>(GetWorld()->GetGameInstance());
	if (nullptr == UpGameInstance)
	{
		UE_LOG(LogTemp, Error, TEXT("BossTruggleSkilLCross : Can't Find GameInstance"));
		return;
	}

	ABossManager* BossManager = UpGameInstance->GetBossManager();
	if (nullptr == BossManager)
	{
		UE_LOG(LogTemp, Error, TEXT("BossTruggleSkilLCross : Can't Find BossManager"));
		return;
	}

	BossDummy = ActorInfo->AvatarActor;
	BossDummy->SetActorTransform(BossManager->GetRandomAroundTransform());

	FTimerHandle FlyForwardTimer;
	GetWorld()->GetTimerManager().SetTimer(FlyForwardTimer, this, &UGA_BossStruggleSkillCross::BossFlyForward, GetWorld()->DeltaTimeSeconds, true);
}


void UGA_BossStruggleSkillCross::BossFlyForward()
{
	FVector NewLocation = BossDummy->GetActorLocation() + (BossDummy->GetActorForwardVector() * GetWorld()->DeltaTimeSeconds * Speed);
	BossDummy->SetActorLocation(NewLocation);
}
