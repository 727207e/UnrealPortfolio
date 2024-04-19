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

	APlayerController* PlayerController = Cast<APlayerController>(NewController);
	if (PlayerController)
	{
		AUPPlayerState* PS = GetPlayerState<AUPPlayerState>();
		if (PS)
		{
			ASC = PS->GetAbilitySystemComponent();
			SetupASCHostPlayer(PS);
			PlayerController->ConsoleCommand(TEXT("showdebug abilitysystem"));
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


UAbilitySystemComponent* AUPBattleBaseCharacter::GetAbilitySystemComponent() const
{
	return ASC;
}

