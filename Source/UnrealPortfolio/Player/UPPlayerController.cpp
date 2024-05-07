// Copyright Epic Games, Inc. All Rights Reserved.

#include "UPPlayerController.h"
#include "GameFramework/Pawn.h"
#include "NiagaraSystem.h"
#include "Character/UPCharacter.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "UI/UPACChatGenerator.h"
#include "GameplayAbilitySpec.h"
#include "Engine/LocalPlayer.h"
#include "InputMappingContext.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

AUPPlayerController::AUPPlayerController()
{
	ChatActorComponent = CreateDefaultSubobject<UUPACChatGenerator>(TEXT("ChatWidgetActorComponent"));
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	PossessCharacter = nullptr;
}

void AUPPlayerController::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}

	PossessCharacter = Cast<IUPPossessCharacterInterface>(GetPawn());
	if (nullptr == PossessCharacter)
	{
		UE_LOG(LogTemplateCharacter, Log, TEXT("Failed To Get PossessCharacter"));
	}


	if(UClass* HudWidgetClass = LoadClass<UUserWidget>(nullptr, TEXT("/Game/UI/WBP_Hud.WBP_Hud_C")))
	{
		MainHudWidget = CastChecked<UUPMainHudWidget>(CreateWidget(GetWorld(),HudWidgetClass,TEXT("UUPMainHudWidget")));
	}
}

void AUPPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->ClearActionBindings();

		// Setup mouse input events
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Started, this, &AUPPlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Triggered, this, &AUPPlayerController::OnSetDestinationTriggered);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Completed, this, &AUPPlayerController::OnSetDestinationReleased);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Canceled, this, &AUPPlayerController::OnSetDestinationReleased);
		
		//SKill
		for (auto& skill : PlayerSkillRegistDictionary)
		{
			EnhancedInputComponent->BindAction(skill.Key, ETriggerEvent::Started, this, &AUPPlayerController::OnSkillStart, skill.Value);
			EnhancedInputComponent->BindAction(skill.Key, ETriggerEvent::Completed, this, &AUPPlayerController::OnSkillRelease, skill.Value);
		}

		//Consumable
		for (auto& item : ConsumableItemDictionary)
		{
			EnhancedInputComponent->BindAction(item.Key, ETriggerEvent::Started, this, &AUPPlayerController::OnConsumableItemStart, item.Value);
		}

		//Widget Interaction
		EnhancedInputComponent->BindAction(ChatEnterAction, ETriggerEvent::Started, this, &AUPPlayerController::ChatFocusOn);
		EnhancedInputComponent->BindAction(ScrollUpAction, ETriggerEvent::Started, this, &AUPPlayerController::ChatScroll, true);
		EnhancedInputComponent->BindAction(ScrollDownAction, ETriggerEvent::Started, this, &AUPPlayerController::ChatScroll, false);

		//Normal Input
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Started, this, &AUPPlayerController::OnAttackStart);
		EnhancedInputComponent->BindAction(AvoidAction, ETriggerEvent::Started, this, &AUPPlayerController::OnAvoidStart);
		EnhancedInputComponent->BindAction(MenuAction, ETriggerEvent::Started, this, &AUPPlayerController::OnMenuStart);
		EnhancedInputComponent->BindAction(InventoryAction, ETriggerEvent::Started, this, &AUPPlayerController::OnInventoryStart);
		
		EnhancedInputComponent->BindAction(InteractionAction, ETriggerEvent::Started, this, &AUPPlayerController::OnNPCInteraction);
		
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AUPPlayerController::OnSkillStart(int32 InputId)
{
	if (PossessCharacter)
	{
		PossessCharacter->OnSkillStart(InputId);
	}
}

void AUPPlayerController::OnSkillRelease(int32 InputId)
{
	if (PossessCharacter)
	{
		PossessCharacter->OnSkillRelease(InputId);
	}
}

void AUPPlayerController::OnAttackStart()
{
	if (PossessCharacter)
	{
		PossessCharacter->OnAttackStart();
	}
}

void AUPPlayerController::OnConsumableItemStart(int32 InputId)
{
	if (PossessCharacter)
	{
		PossessCharacter->OnConsumableStart(InputId);
	}
}

void AUPPlayerController::OnAvoidStart()
{
	if (PossessCharacter)
	{
		PossessCharacter->OnAvoidStart();
	}
}

void AUPPlayerController::OnMenuStart()
{
	if (PossessCharacter)
	{
		PossessCharacter->OnMenuStart();
	}
}

void AUPPlayerController::OnInventoryStart()
{
	if (PossessCharacter)
	{
		PossessCharacter->OnInventoryStart();
	}
}

void AUPPlayerController::OnNPCInteraction()
{
	if (PossessCharacter)
	{
		PossessCharacter->OnNPCInteraction();
	}
}

void AUPPlayerController::ChatFocusOn()
{
	if (ChatActorComponent)
	{
		ChatActorComponent->FocusChat();
	}
}

void AUPPlayerController::ChatScroll(bool bUp)
{
	if (ChatActorComponent)
	{
		ChatActorComponent->Scroll(bUp);
	}
}

UUPMainHudWidget* AUPPlayerController::GetHudWidget()
{
	return  MainHudWidget;
}

void AUPPlayerController::OnInputStarted()
{
	if (PossessCharacter)
	{
		PossessCharacter->OnInputStart();
	}
}

void AUPPlayerController::OnSetDestinationTriggered()
{
	if (PossessCharacter)
	{
		PossessCharacter->OnSetDestinationTriggered();
	}
}

void AUPPlayerController::OnSetDestinationReleased()
{
	if (PossessCharacter)
	{
		PossessCharacter->OnSetDestinationReleased();
	}
}
