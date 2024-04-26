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
#include "GAS/GA/GA_Attack.h"
#include "GAS/GA/GA_NPCInteractor.h"
#include "Gimmick/UPNPCDetectorSceneComponent.h"
#include "Tag/GameplayTags.h"

AUPMainCharacter::AUPMainCharacter()
{
	//ASC = nullptr;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> CharacterMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/DownloadAssets/Primitive_Characters_Pack/Mesh/Primitive_02/Mesh_UE4/Full/SK_Primitive_02_Full.SK_Primitive_02_Full'"));
	if (CharacterMeshRef.Object)
	{
		GetMesh()->SetSkeletalMesh(CharacterMeshRef.Object);
	}
	
	//** Attackable Setup **//
	static ConstructorHelpers::FObjectFinder<UAnimMontage> ComboActionMontageRef(TEXT("/Script/Engine.AnimMontage'/Game/Blueprint/Animation/MainCharacter/Montages/AM_Attack.AM_Attack'"));
	if (ComboActionMontageRef.Object)
	{
		ComboActionMontage = ComboActionMontageRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> DeadActionMontageRef(TEXT("/Script/Engine.AnimMontage'/Game/Blueprint/Animation/MainCharacter/Montages/AM_Dead.AM_Dead'"));
	if (DeadActionMontageRef.Object)
	{
		DeadMontage = DeadActionMontageRef.Object;
	}

	/** Setup Hit Montage **/
	static::ConstructorHelpers::FObjectFinder<UAnimMontage> HitAnimMontageRef(TEXT("/Script/Engine.AnimMontage'/Game/Blueprint/Animation/MainCharacter/Montages/MT_HitBig.MT_HitBig'"));
	if(HitAnimMontageRef.Object)
	{
		HitMontage = HitAnimMontageRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UUPComboActionData> ComboActionDataRef(TEXT("/Script/UnrealPortfolio.UPComboActionData'/Game/Data/AttackData/DA_MainCharacter_Attack.DA_MainCharacter_Attack'"));
	if (ComboActionDataRef.Object)
	{
		ComboActionData = ComboActionDataRef.Object;
	}
	SetupPlayerCamera();
}

UAbilitySystemComponent* AUPMainCharacter::GetAbilitySystemComponent() const
{
	return ASC;
}

void AUPMainCharacter::OnAttackStart()
{
	if(!IsValid(ASC))	{	return; }
	CallGAS(GAS_INPUT_ID_ATTACK_START);
}

void AUPMainCharacter::OnSkillStart(int32 Index)
{
	CallGAS(Index);
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
	CallGAS(GAS_INPUT_ID_AVOID_START);
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

	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController != nullptr && PlayerController->IsLocalPlayerController())
	{
		NPCDetectorSceneComponent = NewObject<UUPNPCDetectorSceneComponent>(this, UUPNPCDetectorSceneComponent::StaticClass());
		NPCDetectorSceneComponent->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("NPC_Checker"));
		NPCDetectorSceneComponent->SetParent(GetRootComponent());
		NPCDetectorSceneComponent->RegisterComponent();
	}
}

void AUPMainCharacter::SetDead()
{
	Super::SetDead();
	SetCharacterMovementMod(MOVE_None);
	PlayDeadAnimation();
	SetActorEnableCollision(false);
}

void AUPMainCharacter::PlayDeadAnimation()
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	AnimInstance->StopAllMontages(0.0f);
	AnimInstance->Montage_Play(DeadMontage,1.0f);
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
	if (NPCDetectorSceneComponent)
	{
		return NPCDetectorSceneComponent->UINPC;
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Log, TEXT("DetectorSceneComponent is null"));
		return nullptr;
	}
}

IUPEntityInterface* AUPMainCharacter::GetNPCEntityInterface()
{
	if (NPCDetectorSceneComponent)
	{
		return NPCDetectorSceneComponent->NPCEntityInterface;
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Log, TEXT("DetectorSceneComponent is null"));
		return nullptr;
	}
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

/** Interface **/
void AUPMainCharacter::SetCharacterMovementMod(EMovementMode MovementMode)
{
	if (!HasAuthority())
	{
		ServerSetControllerMovementMod(MovementMode, Cast<APlayerController>(GetController()));
		return;
	}
	else
	{
		SetControllerMovementMod(MovementMode, GetLocalViewingPlayerController());
	}
}

void AUPMainCharacter::ServerSetControllerMovementMod_Implementation(EMovementMode MovementMode, APlayerController* PlayerController)
{
	SetControllerMovementMod(MovementMode, PlayerController);
}

void AUPMainCharacter::SetControllerMovementMod(EMovementMode MovementMode, APlayerController* PlayerController)
{
	if (MovementMode == EMovementMode::MOVE_None)
	{
		DisableInput(PlayerController);
	}
	else if (MovementMode == MOVE_Walking)
	{
		EnableInput(PlayerController);
	}
	PlayerController->GetCharacter()->GetCharacterMovement()->SetMovementMode(MovementMode);
}

ECharacterControlType AUPMainCharacter::GetCharacterControl()
{
	return CurrentCharacterControlType;
}