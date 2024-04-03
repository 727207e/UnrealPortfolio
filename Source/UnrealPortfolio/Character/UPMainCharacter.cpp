// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/UPMainCharacter.h"
#include "AbilitySystemComponent.h"
#include "Character/UPPlayerState.h"
#include "Interface/UPControllerInterface.h"
#include "Player/UPPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NiagaraFunctionLibrary.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "Components/BoxComponent.h"
#include "Gimmick/UPNPCDetectorSceneComponent.h"

AUPMainCharacter::AUPMainCharacter()
{
	ASC = nullptr;
	NPCDetectorSceneComponent = CreateDefaultSubobject<UUPNPCDetectorSceneComponent>("NPC_Checker");
	NPCDetectorSceneComponent->SetParent(RootComponent);
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

void AUPMainCharacter::OnAttackStart()
{
	UE_LOG(LogTemplateCharacter, Log, TEXT("Attack"));
}

void AUPMainCharacter::OnSkillStart(int32 Index)
{
	UE_LOG(LogTemplateCharacter, Log, TEXT("Start : %d"), Index);
}

void AUPMainCharacter::OnSkillRelease(int32 Index)
{
	UE_LOG(LogTemplateCharacter, Log, TEXT("Release : %d"), Index);
}

void AUPMainCharacter::OnConsumableStart(int32 Index)
{
	UE_LOG(LogTemplateCharacter, Log, TEXT("ConsumableItem : %d"), Index);
}

void AUPMainCharacter::OnAvoidStart()
{
	UE_LOG(LogTemplateCharacter, Log, TEXT("AvoidStart"));
}

void AUPMainCharacter::OnMenuStart()
{
	UE_LOG(LogTemplateCharacter, Log, TEXT("MenuStart"));
}

void AUPMainCharacter::OnInventoryStart()
{
	UE_LOG(LogTemplateCharacter, Log, TEXT("InventoryStart"));
}

void AUPMainCharacter::OnInputStart()
{
	GetController()->StopMovement();
}

void AUPMainCharacter::OnSetDestinationTriggered()
{	
	// We flag that the input is being pressed
	FollowTime += GetWorld()->GetDeltaSeconds();

	// We look for the location in the world where the player has pressed the input
	FHitResult Hit;
	bool bHitSuccessful = false;
	bHitSuccessful = UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);

	// If we hit a surface, cache the location
	if (bHitSuccessful)
	{
		CachedDestination = Hit.Location;
	}

	// Move towards mouse pointer or touch
	FVector WorldDirection = (CachedDestination - this->GetActorLocation()).GetSafeNormal();
	this->AddMovementInput(WorldDirection, 1.0, false);
}

void AUPMainCharacter::OnSetDestinationReleased()
{	
	// If it was a short press
	if (FollowTime <= ShortPressThreshold)
	{
		// We move there and spawn some particles
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(GetController(), CachedDestination);
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursor, CachedDestination, FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);
	}

	FollowTime = 0.f;
}

void AUPMainCharacter::OnNPCInteraction()
{
	UE_LOG(LogTemplateCharacter, Log, TEXT("OnNPCInteraction"));
	NPCDetectorSceneComponent->Action();
}

void AUPMainCharacter::SetupGasInput(AController* NewController)
{
	IUPControllerInterface* ControllerInterface = CastChecked<IUPControllerInterface>(NewController);
	if (ControllerInterface)
	{
		ControllerInterface->SetPossessCharacterInterface(this);
	}
}
