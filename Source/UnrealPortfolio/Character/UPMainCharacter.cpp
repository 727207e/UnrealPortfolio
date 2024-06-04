// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/UPMainCharacter.h"
#include "AbilitySystemComponent.h"
#include "Player/UPPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NiagaraFunctionLibrary.h"
#include "Game/UPGameSingleton.h"
#include "UPPlayerState.h"
#include "Camera/CameraComponent.h"
#include "Components/ArrowComponent.h"
#include "Data/UPCharacterControlData.h"
#include "Data/DataAsset/MainCharacter/UPMainCharacterClassTable.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GAS/GA/GA_Attack.h"
#include "GAS/GA/GA_NPCInteractor.h"
#include "Gimmick/UPNPCDetectorSceneComponent.h"
#include "Item/StaticMeshWeaponComponent.h"
#include "defines/UPServerLogDefine.h"
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

	CreateWeaponComponent();

	AvoidDirectionArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("AvoidDirectionArrowComponent"));
	AvoidDirectionArrowComponent->SetupAttachment(RootComponent);
	AvoidDirectionArrowComponent->ArrowLength = 400;
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

void AUPMainCharacter::Server_SetActorRotation_Implementation(FVector LookTargetLocation)
{
	LookTarget(LookTargetLocation);
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
	if(!bLockMove)
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
	
}

void AUPMainCharacter::OnSetDestinationReleased()
{
	if(!bLockMove)
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
	if (HasAuthority())
	{
		AUPPlayerController* HostController =  Cast<AUPPlayerController>(GetWorld()->GetFirstPlayerController());
		if(HostController->PlayerState)
		{
			AActor* PS = HostController->PlayerState;
			HostController->HudWidgetComponent->MainHudWidget = CastChecked<UUPMainHudWidget>(CreateWidget(GetWorld(),HostController->HudWidgetComponent->HudWidgetClass
,TEXT("UUPMainHudWidget")));
			HostController->HudWidgetComponent->MainHudWidget->AddToViewport();
			HostController->HudWidgetComponent->MainHudWidget->SetProgress(PS);
		}
	}
	
}

void AUPMainCharacter::CallGAS(int32 GameplayAbilityInputId)
{
	const bool bHasAvoidTag = ASC->HasMatchingGameplayTag(TAG_PLAYER_STATE_AVOID);
	const bool bHasInteractingTag = ASC->HasMatchingGameplayTag(TAG_PLAYER_INTERACTING_WITH_NPC);

	if (GameplayAbilityInputId == GAS_INPUT_ID_AVOID_START)
	{
		if (!bHasAvoidTag && !bHasInteractingTag)
		{
			Super::CallGAS(GameplayAbilityInputId);
		}
	}
	else
	{
		const bool bHasAttackSkillTag = ASC->HasMatchingGameplayTag(TAG_PLAYER_STATE_ATTACK_SKILL);

		if (!bHasAvoidTag && !bHasInteractingTag && !bHasAttackSkillTag)
		{
			CharacterLookMouseLocation();
			Super::CallGAS(GameplayAbilityInputId);
		}
	}
}

void AUPMainCharacter::SetDead()
{
	Super::SetDead();
	//버그 임시 주석
	//SetCharacterMovementMod(MOVE_None);
	PlayDeadAnimation();
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

void AUPMainCharacter::SetMainCharacterTableData() const
{
    const auto MainCharacterData = UUPGameSingleton::Get().GetCurrentMainCharacterData();
	GetMesh()->SetSkeletalMesh(MainCharacterData.Mesh);
	AttributeSet->InitAttributeSet();
	AttributeSet->OnDead.AddDynamic(this,&ThisClass::OnDead);
}

void AUPMainCharacter::SetupASCClientPlayer()
{
	Super::SetupASCClientPlayer();
	CreateHudWidget();
	SetMainCharacterTableData();
	ActiveAbilityEquipWeapon(DEFAULT_WEAPON_ID);
}

void AUPMainCharacter::SetupASCHostPlayer(AActor* InOwnerActor)
{
	Super::SetupASCHostPlayer(InOwnerActor);
	CreateHudWidget();
	SetMainCharacterTableData();
	ActiveAbilityEquipWeapon(DEFAULT_WEAPON_ID);
}



// Need refactoring for the listening server
void AUPMainCharacter::OnDead()
{
	Super::OnDead();
	APlayerController* DeadPlayerController = Cast<APlayerController>(GetController());
	if(DeadPlayerController)
	{
		DisableInput(DeadPlayerController);
	}
}

void AUPMainCharacter::ActiveAbilityGameOverCheck()
{
	if(HasAuthority() && GetController()) 
	{
		const bool IsLocal = GetController()->IsLocalController();
		const bool IsPlayer = GetController()->IsPlayerController();
		
		if(IsLocal && IsPlayer)
		{
			FGameplayAbilitySpec* Spec = ASC->FindAbilitySpecFromClass(StartAbilities[GAS_START_ABILITY_ID_GAME_RESULT]);
			if(Spec)
			{
				ASC->TryActivateAbility(Spec->Handle);
			}		
		}
	}
}

void AUPMainCharacter::ActiveAbilityEquipWeapon(int32 TryEquipWeaponId)
{
	if(!IsValid(ASC) || WeaponComponent == nullptr)	{	return; }
	
	const FGameplayTagContainer TargetTag(TAG_WEAPON);
	if(!ASC->HasMatchingGameplayTag(TAG_CHARACTER_STATE_EQUIP_WEAPON))
	{
		WeaponComponent->SetWeaponId(TryEquipWeaponId);
		const FUPWeaponTable WeaponModelData = UUPGameSingleton::Get().WeaponTablesArray[WeaponComponent->GetWeaponId()];
		WeaponComponent->SetWeaponData(WeaponModelData);
		ASC->TryActivateAbilitiesByTag(TargetTag);
	}
	else
	{
		ASC->CancelAbilities(&TargetTag);
	}
}



AUPPlayerState* AUPMainCharacter::GetUPPlayerState()
{
	return Cast<AUPPlayerState>(GetPlayerState());  
}

UStaticMeshWeaponComponent* AUPMainCharacter::GetEquipWeapon()
{
	return WeaponComponent;
}

void AUPMainCharacter::CreateWeaponComponent()
{
	WeaponComponent = CreateDefaultSubobject<UStaticMeshWeaponComponent>(TEXT("WeaponComponent"));
	WeaponComponent->SetupAttachment(GetMesh(), SocketWeapon);
}

void AUPMainCharacter::CharacterLookMouseLocation()
{
	if (IsLocallyControlled())
	{
		FHitResult Hit;
		bool bHitSuccessful = false;
		bHitSuccessful = UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);

		if (bHitSuccessful)
		{
			LookTarget(Hit.Location);

			if (!HasAuthority())
			{
				Server_SetActorRotation(Hit.Location);
			}
		}
	}
}

void AUPMainCharacter::CreateHudWidget()
{
	AUPPlayerState* PS = GetPlayerState<AUPPlayerState>();
	AUPPlayerController* MyClienetController = Cast<AUPPlayerController>(PS->GetPlayerController());
	if(MyClienetController)
	{
		if(MyClienetController)
		{
			MyClienetController->HudWidgetComponent->MainHudWidget = CastChecked<UUPMainHudWidget>(CreateWidget(GetWorld(),MyClienetController->HudWidgetComponent->HudWidgetClass
	,TEXT("UUPMainHudWidget")));
			MyClienetController->HudWidgetComponent->MainHudWidget->AddToViewport();
			MyClienetController->HudWidgetComponent->MainHudWidget->SetProgress(PS);
			
		}
	}
}

void AUPMainCharacter::SetMoveBlock(bool bBlock)
{
	bLockMove = bBlock;
}

void AUPMainCharacter::Dodge()
{
	LaunchCharacter(AvoidDirectionArrowComponent->GetForwardVector() * 2300,true,false);	
}



ECharacterControlType AUPMainCharacter::GetCharacterControl()
{
	return CurrentCharacterControlType;
}

