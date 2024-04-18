// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/UPBattleBaseCharacter.h"
#include "AbilitySystemComponent.h"
#include "UPPlayerState.h"

AUPBattleBaseCharacter::AUPBattleBaseCharacter()
{
	ASC = nullptr;
	
}

void AUPBattleBaseCharacter::SetDead()
{
}


void AUPBattleBaseCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	if(NewController)
	{
		SetupASCHostPlayer();
		APlayerController* PlayerController = CastChecked<APlayerController>(NewController);
		PlayerController->ConsoleCommand(TEXT("showdebug abilitysystem"));
	}
}

void AUPBattleBaseCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	SetupASCClientPlayer();
}


void AUPBattleBaseCharacter::SetupASCHostPlayer()
{
	AUPPlayerState* PS = GetPlayerState<AUPPlayerState>();
	if (PS)
	{
		ASC = PS->GetAbilitySystemComponent();
		ASC->InitAbilityActorInfo(PS, this);

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
}

void AUPBattleBaseCharacter::SetupASCClientPlayer()
{
	AUPPlayerState* PS = GetPlayerState<AUPPlayerState>();
	if (PS)
	{
		ASC = PS->GetAbilitySystemComponent();
		ASC->InitAbilityActorInfo(PS, this);
	}
}

void AUPBattleBaseCharacter::SetupASCEnemyCharacter()
{
	ASC->InitAbilityActorInfo(this, this);
	ASC->SetIsReplicated(true);
	ASC->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
}


UAnimMontage* AUPBattleBaseCharacter::GetComboActionMontage()
{
	if (ComboActionMontage)
	{
		return ComboActionMontage;
	}

	return nullptr;
}


UAbilitySystemComponent* AUPBattleBaseCharacter::GetAbilitySystemComponent() const
{
	return ASC;
}

