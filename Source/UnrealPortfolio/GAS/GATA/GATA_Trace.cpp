// Fill out your copyright notice in the Description page of Project Settings.


#include "GATA_Trace.h"
#include "Abilities/GameplayAbility.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"
#include "DrawDebugHelpers.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Data/DataAttributeSet/EntityAttributeSet.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "defines/UPCollision.h"
#include "AbilitySystemComponent.h"
#include "GAS/Attribute/UPMainCharacterAttributeSet.h"
#include "Data/DataAttributeSet/EntityAttributeSet.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "defines/UPServerLogDefine.h"

AGATA_Trace::AGATA_Trace()
{
	
}

void AGATA_Trace::StartTargeting(UGameplayAbility* Ability)
{
	Super::StartTargeting(Ability);
	SourceActor = Ability->GetCurrentActorInfo()->AvatarActor.Get();
}

void AGATA_Trace::ConfirmTargetingAndContinue()
{
	if(SourceActor)
	{
		const FGameplayAbilityTargetDataHandle DataHandle = MakeTargetData();
		TargetDataReadyDelegate.Broadcast(DataHandle);
	}
}

FGameplayAbilityTargetDataHandle AGATA_Trace::MakeTargetData() const
{
	FGameplayAbilityTargetDataHandle DataHandle;
	ACharacter* Character = CastChecked<ACharacter>(SourceActor);
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(SourceActor);
	if (nullptr == TargetASC)
	{
		UE_LOG(LogTemp, Error, TEXT("Enemy Can't Find ASC"));
		return DataHandle;
	}

	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(SourceActor);
	if(!ASC)
	{
		return FGameplayAbilityTargetDataHandle();
	}

	const UEntityAttributeSet* AttributeSet = ASC->GetSet<UEntityAttributeSet>();
	if(!AttributeSet)
	{
		UE_LOG(LogTemp, Error, TEXT("TA Trace Can't Find AttributeSet"));
		return FGameplayAbilityTargetDataHandle();
	}
	
	FHitResult OutHitResult;
	const float AttackRange = AttributeSet->GetAttackRange();
	const float AttackRadius = AttributeSet->GetAttackRadius();

	FCollisionQueryParams Params(SCENE_QUERY_STAT(CHANNEL_UPTRACE), false, Character);
	const FVector Forward = Character->GetActorForwardVector();
	const FVector Start = Character->GetActorLocation() + Forward * Character->GetCapsuleComponent()->GetScaledCapsuleRadius();
	const FVector End = Start + Forward * AttackRange;

	bool HitDetected = GetWorld()->SweepSingleByChannel(OutHitResult, Start, End, FQuat::Identity, CHANNEL_UPTRACE, FCollisionShape::MakeSphere(AttackRadius), Params);
	
	if (HitDetected)
	{
		FGameplayAbilityTargetData_SingleTargetHit* TargetData = new FGameplayAbilityTargetData_SingleTargetHit(OutHitResult);
		DataHandle.Add(TargetData);
	}

#if ENABLE_DRAW_DEBUG

	if (bShowDebug)
	{
		FVector CapsuleOrigin = Start + (End - Start) * 0.5f;
		float CapsuleHalfHeight = AttackRange * 0.5f;
		FColor DrawColor = HitDetected ? FColor::Green : FColor::Red;
		DrawDebugCapsule(GetWorld(), CapsuleOrigin, CapsuleHalfHeight, AttackRadius, FRotationMatrix::MakeFromZ(Forward).ToQuat(), DrawColor, false, 5.0f);
	}

#endif

	return DataHandle;
}