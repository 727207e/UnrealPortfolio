// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/UPMainCharacter.h"
#include "AbilitySystemComponent.h"
#include "Character/UPPlayerState.h"
#include "Player/UPPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NiagaraFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Data/UPCharacterControlData.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GAS/GA/GA_NPCInteractor.h"
#include "Gimmick/UPNPCDetectorSceneComponent.h"
#include "Tag/GameplayTags.h"



AUPMainCharacter::AUPMainCharacter()
{
	ASC = nullptr;
	NPCDetectorSceneComponent = CreateDefaultSubobject<UUPNPCDetectorSceneComponent>("NPC_Checker");
	NPCDetectorSceneComponent->SetParent(RootComponent);
	
	SetupPlayerCamera();
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
	if(!IsValid(ASC))	{	return; }
	
	const FGameplayTagContainer TargetTag(TAG_ACTOR_INTERACTION);
	if(!ASC->HasMatchingGameplayTag(TAG_PLAYER_INTERACTING_WITH_NPC))
	{
		ASC->TryActivateAbilitiesByTag(TargetTag);
	}
	else
	{
		ASC->CancelAbilities(&TargetTag);
	}
}

void AUPMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	SetCharacterControl(ECharacterControlType::TopDown);
}


void AUPMainCharacter::SetupGasInput(AController* NewController)
{
	IUPControllerInterface* ControllerInterface = CastChecked<IUPControllerInterface>(NewController);
	if (ControllerInterface)
	{
		ControllerInterface->SetPossessCharacterInterface(this);
	}
}


IUPUINpcInterface* AUPMainCharacter::GetNPCInterface()
{
	return  NPCDetectorSceneComponent->UINPC;
}

//*##############################Camera Control##################################*/
//*##############################Camera Control##################################*/



void AUPMainCharacter::SetupPlayerCamera()
{
	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	CameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Create CharacterControlData...
	static ConstructorHelpers::FObjectFinder<UUPCharacterControlData> ShoulderDataRef(TEXT("/Script/UnrealPortfolio.UPCharacterControlData'/Game/CharacterControl/ABC_Shoulder.ABC_Shoulder'"));
	if (ShoulderDataRef.Object)
	{
		CharacterControlManager.Add(ECharacterControlType::Shoulder, ShoulderDataRef.Object);
	}

	static ConstructorHelpers::FObjectFinder<UUPCharacterControlData> TopDownDataDataRef(TEXT("/Script/UnrealPortfolio.UPCharacterControlData'/Game/CharacterControl/ABC_TopDown.ABC_TopDown'"));
	if (TopDownDataDataRef.Object)
	{
		CharacterControlManager.Add(ECharacterControlType::TopDown, TopDownDataDataRef.Object);
	}

	static ConstructorHelpers::FObjectFinder<UUPCharacterControlData> SideScrollDataRef(TEXT("/Script/UnrealPortfolio.UPCharacterControlData'/Game/CharacterControl/ABC_SideScroll.ABC_SideScroll'"));
	if (SideScrollDataRef.Object)
	{
		CharacterControlManager.Add(ECharacterControlType::SideScroll, SideScrollDataRef.Object);
	}

	static ConstructorHelpers::FObjectFinder<UUPCharacterControlData> NPCCameraDataRef(TEXT("/Script/UnrealPortfolio.UPCharacterControlData'/Game/CharacterControl/ABC_NPCCamera.ABC_NPCCamera'"));
	if (NPCCameraDataRef.Object)
	{
		CharacterControlManager.Add(ECharacterControlType::NPC, NPCCameraDataRef.Object);
	}
}

void AUPMainCharacter::SetCharacterControl(ECharacterControlType NewCharacterControlType, FTransform TargetTransform)
{
	UUPCharacterControlData* NewCharacterControl = CharacterControlManager[NewCharacterControlType];
	check(NewCharacterControl);

	SetCharacterControlData(NewCharacterControl);
	SetCameraComponent(NewCharacterControlType, TargetTransform);
	CurrentCharacterControlType = NewCharacterControlType;
}

void AUPMainCharacter::SetCharacterControlData(const UUPCharacterControlData* CharacterControlData)
{
	CameraBoom->TargetArmLength = CharacterControlData->TargetArmLength;
	CameraBoom->SetRelativeRotation(CharacterControlData->RelativeRotation);
	CameraBoom->bUsePawnControlRotation = CharacterControlData->bUsePawnControlRotation;
	CameraBoom->bInheritPitch = CharacterControlData->bInheritPitch;
	CameraBoom->bInheritYaw = CharacterControlData->bInheritYaw;
	CameraBoom->bInheritRoll = CharacterControlData->bInheritRoll;
	CameraBoom->bDoCollisionTest = CharacterControlData->bDoCollisionTest;
}

void AUPMainCharacter::SetCameraComponent(ECharacterControlType CharacterControlType, FTransform CameraTransform)
{
	if (CharacterControlType == ECharacterControlType::NPC)
	{
		CameraComponent->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	}
	else
	{
		CameraComponent->AttachToComponent(CameraBoom, FAttachmentTransformRules::KeepRelativeTransform);
	}

	CameraComponent->SetRelativeTransform(CameraTransform);
}

void AUPMainCharacter::GASInputPressed(int32 GameplayAbilityInputId)
{ 
	FGameplayAbilitySpec* Spec = ASC->FindAbilitySpecFromInputID(GameplayAbilityInputId);
	if(Spec)
	{
		Spec->InputPressed = true;
		if(Spec->IsActive())
		{
			ASC->AbilitySpecInputPressed(*Spec);
		}
		else
		{
			ASC->TryActivateAbility(Spec->Handle);
		}
	}
	
}

/** Interface **/
void AUPMainCharacter::SetCharacterMovementMod(EMovementMode MovementMode)
{
	GetCharacterMovement()->SetMovementMode(MovementMode);
}

ECharacterControlType AUPMainCharacter::GetCharacterControl()
{
	return CurrentCharacterControlType;
}
