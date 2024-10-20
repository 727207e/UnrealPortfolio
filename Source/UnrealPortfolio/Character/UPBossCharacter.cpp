// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/UPBossCharacter.h"
#include "AI/UPBossAIController.h"
#include "Tag/GameplayTags.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GAS/Attribute/BossDataSet/UPBossSkillAttributeSet.h"
#include "GAS/State/UPACSkillState.h"
#include "GAS/GA/Skill/GA_SkillBase.h"

AUPBossCharacter::AUPBossCharacter()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> CharacterMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/DownloadAssets/DemonessBoss/Mesh/SK_DemonessBoss.SK_DemonessBoss'"));
	if (CharacterMeshRef.Object)
	{
		GetMesh()->SetSkeletalMesh(CharacterMeshRef.Object);
	}

	static ConstructorHelpers::FClassFinder<UAnimInstance> CharacterAnimRef(TEXT("/Game/Blueprint/Animation/Enemy/Boss/ABP_BossEnemy.ABP_BossEnemy_C"));
	if (CharacterAnimRef.Class)
	{
		GetMesh()->SetAnimInstanceClass(CharacterAnimRef.Class);
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> ComboMontageRef(TEXT("/Script/Engine.AnimMontage'/Game/Blueprint/Animation/Enemy/Boss/AM_BossNormalAttack.AM_BossNormalAttack'"));
	if (ComboMontageRef.Object)
	{
		ComboActionMontage = ComboMontageRef.Object;
	}

	AIControllerClass = AUPBossAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	AttackDelayTime = 5;
	CounterResetDelayTime = 1.0f;
}

void AUPBossCharacter::PreInitializeComponents()
{
	Super::PreInitializeComponents();

	if (BossSkillStateForm)
	{
		for (int32 Index = 0; Index < BossSkillAttributeSetTypeArray.Num(); Index++)
		{
			TSubclassOf<UUPBossSkillAttributeSet> SkillAttributeSet = BossSkillAttributeSetTypeArray[Index];
			UUPACSkillState* SkillState = NewObject<UUPACSkillState>(this, BossSkillStateForm);
			if (SkillState)
			{
				this->AddOwnedComponent(SkillState);
				SkillState->RegisterComponent();
				SkillState->InitSkillState(this, SkillAttributeSet, Index);
				BossSkillStateArray.Add(SkillState);
			}
		}
	}
}

void AUPBossCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(this);
	if (nullptr == TargetASC)
	{
		return;
	}
	else
	{
		TargetASC->AddLooseGameplayTag(TAG_HEAD_ATTACK_HIT);
		TargetASC->AddLooseGameplayTag(TAG_BACK_ATTACK_HIT);
	}

	UpdatePhaseNumber(CurPhaseNumber);
}

void AUPBossCharacter::SkillEndCallBack()
{
	Super::SkillEndCallBack();

	SetAttackDelay(AttackDelayTime);
}

void AUPBossCharacter::CounterAttackHit()
{
	AUPBossAIController* BossController = Cast<AUPBossAIController>(GetController());
	if (nullptr == BossController)
	{
		UE_LOG(LogTemp, Error, TEXT("UPBossCharacter Can't Find Controller"));
		return;
	}
	
	BossController->SetBossCanMove(false);

	ASC->RemoveLooseGameplayTag(TAG_COUNTER_HIT);

	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	AnimInstance->Montage_Play(GroggyMontage);
	AnimInstance->OnMontageEnded.AddDynamic(this, &AUPBossCharacter::MontageEndEvent);

	if (CurSkillGA != nullptr)
	{
		CurSkillGA->EndGA();
	}
}

void AUPBossCharacter::UpdatePhaseNumber(int32 PhaseNumber)
{
	CurPhaseNumber = PhaseNumber;
	for (TObjectPtr<UUPACSkillState> SkillState : BossSkillStateArray)
	{
		SkillState->PostInitialize(CurPhaseNumber);
	}
}

void AUPBossCharacter::MontageEndEvent(UAnimMontage* Montage, bool bInterrupted)
{
	FTimerHandle FollowDelay;
	FTimerHandle DeadTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(DeadTimerHandle, FTimerDelegate::CreateLambda([&] {
		AUPBossAIController* BossController = Cast<AUPBossAIController>(GetController());
		if (nullptr == BossController)
		{
			UE_LOG(LogTemp, Error, TEXT("UPBossCharacter Can't Find Controller"));
			return;
		}

		BossController->SetBossCanMove(true);

		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
		AnimInstance->OnMontageEnded.RemoveDynamic(this, &AUPBossCharacter::MontageEndEvent);
	}), CounterResetDelayTime, false);
	
}

void AUPBossCharacter::OnDead()
{
	Super::OnDead();
	ASC->AddLooseGameplayTag(TAG_CHARACTER_BOSS_IS_DEAD);
}

UAbilitySystemComponent* AUPBossCharacter::GetBossAbilitySystemComponent()
{
	return  ASC;
}
