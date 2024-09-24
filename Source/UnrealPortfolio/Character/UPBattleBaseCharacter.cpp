// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/UPBattleBaseCharacter.h"
#include "AbilitySystemComponent.h"
#include "Game/UPGameSingleton.h"
#include "UPPlayerState.h"
#include "Data/DataTable/UPActionTable.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GAS/Actor/GameplayEventDataRequest.h"
#include "Tag/GameplayTags.h"

AUPBattleBaseCharacter::AUPBattleBaseCharacter()
{
	ASC = nullptr;

	bCanAttack = true;
}

void AUPBattleBaseCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	APlayerController* PlayerController = Cast<APlayerController>(NewController);
	if (PlayerController)
	{
		AUPPlayerState* PS = GetPlayerState<AUPPlayerState>();
		if (PS)
		{
			ASC = PS->GetAbilitySystemComponent();
			AttributeSet = PS->GetMainCharacterAttributeSet();
			SetupASCHostPlayer(PS);
			//PlayerController->ConsoleCommand(TEXT("showdebug abilitysystem"));
		}
	}

	else // AI Controller
	{
		if(HasAuthority())
		{
			SetupASCHostPlayer(this);
		}

		else
		{
			ServerASCSyncRequest();
		}
	}
}

void AUPBattleBaseCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	SetupASCClientPlayer();
}

void AUPBattleBaseCharacter::ServerASCSyncRequest_Implementation()
{
	//Need Refactoring 
	SetupASCHostPlayer(this);
}


void AUPBattleBaseCharacter::SetupASCHostPlayer(AActor* InOwnerActor)
{
	ASC->InitAbilityActorInfo(InOwnerActor, this);

	for (const auto& StartAbility : StartAbilities)
	{
		FGameplayAbilitySpec StartSpec(StartAbility);
		ASC->GiveAbility(StartSpec);
	}

	for (const auto& StartInputAbility : StartInputAbilities)
	{
		FGameplayAbilitySpec StartSpec(StartInputAbility.Value);
		StartSpec.InputID = StartInputAbility.Key;
		ASC->GiveAbility(StartSpec);
	}
}

void AUPBattleBaseCharacter::SetupASCClientPlayer()
{
	AUPPlayerState* PS = GetPlayerState<AUPPlayerState>();
	if (PS)
	{
		ASC = PS->GetAbilitySystemComponent();
		ASC->InitAbilityActorInfo(PS, this);
		AttributeSet = PS->GetMainCharacterAttributeSet();
	}
}

UAnimMontage* AUPBattleBaseCharacter::GetComboActionMontage()
{
	if (ComboActionMontage)
	{
		return ComboActionMontage;
	}

	return nullptr;
}

void AUPBattleBaseCharacter::CallGAS(int32 GameplayAbilityInputId)
{
	FGameplayAbilitySpec* Spec = ASC->FindAbilitySpecFromInputID(GameplayAbilityInputId);
	UsingGAArray.Add(*Spec);

	if (Spec)
	{
		Spec->InputPressed = true;
		if (Spec->IsActive())
		{
			ASC->AbilitySpecInputPressed(*Spec);
		}
		else
		{
			ASC->TryActivateAbility(Spec->Handle);
		}
	}
}

TArray<FGameplayAbilitySpec> AUPBattleBaseCharacter::GetUsingGas(int32 GameplayAbilityInputId)
{
	TArray<FGameplayAbilitySpec> Result;

	for (FGameplayAbilitySpec GASpec : UsingGAArray)
	{
		if (GASpec.InputID == GameplayAbilityInputId)
		{
			Result.Add(GASpec);
		}
	}

	return Result;
}

void AUPBattleBaseCharacter::Hit(FVector TargetLocation, TObjectPtr<class AGameplayEventDataRequest> ActionData)
{
	LookTarget(TargetLocation);
	//Knockback(ActionData);
	PlayHitAnimation();
}

void AUPBattleBaseCharacter::PlayHitAnimation()
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if(HitMontage && AnimInstance)
	{
		AnimInstance->Montage_Play(HitMontage);
	}

	OnHitDelegate.Broadcast();
}

void AUPBattleBaseCharacter::Knockback(TObjectPtr<class AGameplayEventDataRequest> ActionData)
{
	const FText RowTableName = FText::FromName( ActionData->ActionRowName);
	const FString RowTableNameString = RowTableName.ToString();
	const TCHAR* RowTableNamePtr = *RowTableNameString;
	const FName NextSection = *FString::Printf(TEXT("%s%d"), RowTableNamePtr, ActionData->ActionId);

	const auto ActionTableData  = UUPGameSingleton::Get().ActionDataTable;
	if(const FUPActionTable* ActionRowData = ActionTableData->FindRow<FUPActionTable>(FName(NextSection),TEXT("Finding Row")))
	{
		FVector BreakVector = GetActorForwardVector() * ActionRowData->NockbackDuration;
		BreakVector.X = BreakVector.X + ActionRowData->NockbackSize;
		BreakVector.Z = ActionRowData->NockbackUpSize;
		LaunchCharacter(BreakVector,true,false);
	}
}


void AUPBattleBaseCharacter::OnDead()
{
	SetActorEnableCollision(false);
}

void AUPBattleBaseCharacter::SetAttackDelay(float DelayTime)
{
	GetWorld()->GetTimerManager().SetTimer(AttackDelay, FTimerDelegate::CreateLambda([=, this] 
		{
			bCanAttack = true;
		}), DelayTime, false);
}

void AUPBattleBaseCharacter::AttackEndCallBack()
{
	OnEndAttackDelegate.Broadcast();
	OnEndAttackDelegate.Clear();
}

void AUPBattleBaseCharacter::AddAttackEndCallBack(const FOnEndAttackDelegate& OnEndAttack)
{
	OnEndAttackDelegate = OnEndAttack;
}

void AUPBattleBaseCharacter::SkillEndCallBack()
{
	OnEndSkillDelegate.Broadcast();
	OnEndSkillDelegate.Clear();
}

void AUPBattleBaseCharacter::NormalAttack()
{
	
}

void AUPBattleBaseCharacter::OnSkill(int32 SkillNumber)
{
	TArray<FGameplayAbilitySpecHandle> ActivatedAbilities;
	ASC->FindAllAbilitiesWithTags(ActivatedAbilities, FGameplayTagContainer(TAG_CHARACTER_SKILL));
	if (ActivatedAbilities.IsEmpty() || ActivatedAbilities.Num() < SkillNumber)
	{
		UE_LOG(LogTemp, Error, TEXT("BattleBaseCharacter OnSkill Has No Skill"));
		return;
	}

	ASC->TryActivateAbility(ActivatedAbilities[SkillNumber]);
}

void AUPBattleBaseCharacter::AddOnHitDelegate(FOnHitDelegate& Delegate)
{
	OnHitDelegate = Delegate;
}

UAbilitySystemComponent* AUPBattleBaseCharacter::GetAbilitySystemComponent() const
{
	return ASC;
}