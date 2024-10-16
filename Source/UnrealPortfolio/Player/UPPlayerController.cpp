// Copyright Epic Games, Inc. All Rights Reserved.

#include "UPPlayerController.h"
#include "GameFramework/Pawn.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "UI/UPACChatGenerator.h"
#include "Engine/LocalPlayer.h"
#include "Game/UPGameSingleton.h"
#include "InputMappingContext.h"

class AUPPlayerState;
DEFINE_LOG_CATEGORY(LogTemplateCharacter);

AUPPlayerController::AUPPlayerController()
{
	ChatActorComponent = CreateDefaultSubobject<UUPACChatGenerator>(TEXT("ChatWidgetActorComponent"));
	HudWidgetComponent = CreateDefaultSubobject<UWidgetHUDComponent>(TEXT("HudComponent"));
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

	SkillSetting();

	if (IsLocalController())
	{
		HudWidgetComponent->MainHudWidget = CastChecked<UUPMainHudWidget>(CreateWidget(GetWorld(), HudWidgetComponent->HudWidgetClass));
		HudWidgetComponent->MainHudWidget->AddToViewport();
		HudWidgetComponent->MainHudWidget->SetProgress(GetPlayerState<AUPPlayerState>());
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

void AUPPlayerController::SkillSetting()
{
	SkillCoolDownData.Init(false, UUPGameSingleton::Get().SkillDataArray.Num());
}

bool AUPPlayerController::IsSkillCoolDown(int32 SkillNumber)
{
	if (SkillNumber > SkillCoolDownData.Num())
	{
		UE_LOG(LogTemp, Error, TEXT("AUPMainCharacter::IsSkillCoolDown : SkillNumber is Higher than SkillArray"));
		return true;
	}

	return SkillCoolDownData[SkillNumber];
}

void AUPPlayerController::SkillSettingCoolDown(int32 SkillNumber, int32 SkillCoolDown)
{
	if (SkillCoolDownData[SkillNumber])
	{
		return;
	}

	if (IsLocalController())
	{
		HudWidgetComponent->MainHudWidget->TargetButtonPress(SkillNumber, SkillCoolDown);
	}

	SkillCoolDownData[SkillNumber] = true;

	FTimerHandle CooldownTimer;	
	GetWorld()->GetTimerManager().SetTimer(CooldownTimer, FTimerDelegate::CreateLambda([&, SkillNumber]
		{
			SkillCoolDownData[SkillNumber] = false;
		}), SkillCoolDown, false);
}

void AUPPlayerController::BuffIconActive()
{
	if (IsLocalController())
	{
		GetHudWidget()->BuffProcess();
	}
	else if(HasAuthority())
	{
		Client_BuffIconActive();
	}
}

void AUPPlayerController::Client_BuffIconActive_Implementation()
{
	BuffIconActive();
}

