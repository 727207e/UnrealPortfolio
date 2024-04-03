// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/UPMainCharacter.h"
#include "AbilitySystemComponent.h"
#include "Character/UPPlayerState.h"
#include "Player/UPPlayerController.h"
#include "Abilities/GameplayAbilityTypes.h"

AUPMainCharacter::AUPMainCharacter()
{
	ASC = nullptr;
}

UAbilitySystemComponent* AUPMainCharacter::GetAbilitySystemComponent() const
{
	return ASC;
}

void AUPMainCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	AUPPlayerState* GASPS = GetPlayerState<AUPPlayerState>();
	if (GASPS)
	{
		ASC = GASPS->GetAbilitySystemComponent();
		ASC->InitAbilityActorInfo(GASPS, this);

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

		SetupGasInput(NewController);

		APlayerController* PlayerController = CastChecked<APlayerController>(NewController);
		PlayerController->ConsoleCommand(TEXT("showdebug abilitysystem"));
	}
}

void AUPMainCharacter::SetupGasInput(AController* NewController)
{
	//AUPPlayerController* PlayerController = CastChecked<AUPPlayerController>(NewController);
	//if (PlayerController && IsValid(ASC) && IsValid(InputComponent))
	//{
	//	
	//}
}
