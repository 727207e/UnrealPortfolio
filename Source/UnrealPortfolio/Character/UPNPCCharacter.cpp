// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/UPNPCCharacter.h"
#include "defines/UPCollision.h"
#include "Components/CapsuleComponent.h"
#include "Components/SceneComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/WidgetComponent.h"

// Sets default values
AUPNPCCharacter::AUPNPCCharacter()
{
	// Capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	GetCapsuleComponent()->SetCollisionProfileName(CPROFILE_UP_NPC);
	
	// Mesh
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -100.0f), FRotator(0.0f, -90.0f, 0.0f));
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	GetMesh()->SetCollisionProfileName(CPROFILE_UP_NPC);

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> CharacterMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/DownloadAssets/Primitive_Characters_Pack/Mesh/Primitive_02/Mesh_UE4/Full/SK_Primitive_02_Full.SK_Primitive_02_Full'"));
	if (CharacterMeshRef.Object)
	{
		GetMesh()->SetSkeletalMesh(CharacterMeshRef.Object);
	}

	static ConstructorHelpers::FClassFinder<UAnimInstance> CharacterAnimRef(TEXT("/Game/Blueprint/Animation/ABP_Dwarf.ABP_Dwarf_C"));

	if(CharacterAnimRef.Class)
	{
		GetMesh()->SetAnimInstanceClass(CharacterAnimRef.Class);
	}
	
	InteractionAlarmCompo = CreateDefaultSubobject<UWidgetComponent>(TEXT("InterActionCompo"));
	InteractionAlarmCompo->SetupAttachment(GetMesh());			
	static ConstructorHelpers::FClassFinder<UUserWidget> InterActionClassRef(TEXT("/Game/UI/WBP_InteractionAlarm.WBP_InteractionAlarm_C"));
	if(InterActionClassRef.Class)
	{
		InteractionAlarmCompo->SetWidgetClass(InterActionClassRef.Class);
		InteractionAlarmCompo->SetWidgetSpace(EWidgetSpace::World);
		InteractionAlarmCompo->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	
	NPCCameraTransform = CreateDefaultSubobject<USceneComponent>(TEXT("CameraTransform"));
	NPCCameraTransform->SetupAttachment(RootComponent);
	SetReplicateMovement(false);
}

void AUPNPCCharacter::TakeNPCWidgetShow()
{
	if (NPCUI != nullptr)
	{
		NPCUI->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		NPCUI = CreateWidget(GetWorld(), NPCUIType);
		NPCUI->AddToViewport();
	}
}

void AUPNPCCharacter::TakeNPCWidgetHide()
{
	if (NPCUI != nullptr)
	{
		NPCUI->SetVisibility(ESlateVisibility::Hidden);
	}
}

void AUPNPCCharacter::BeginPlay()
{
	Super::BeginPlay();
	InteractionAlarmCompo->GetWidget()->AddToViewport();
	HideInterActionAlarm();
}

FTransform AUPNPCCharacter::GetNPCCameraTransform()
{
	return NPCCameraTransform->GetComponentTransform();
}

void AUPNPCCharacter::LookTarget(const FVector& TargetLocation)
{
	FVector TargetDirection = TargetLocation - GetActorLocation();
	TargetDirection.Z = 0;

	SetActorRotation(TargetDirection.Rotation());
}

FVector AUPNPCCharacter::GetCurLocation()
{
	return GetActorLocation();
}

void AUPNPCCharacter::ShowInteractionAlarm()
{
	if(InteractionAlarmCompo)
	{
		InteractionAlarmCompo->GetWidget()->SetVisibility(ESlateVisibility::Visible);	
	}
}

void AUPNPCCharacter::HideInterActionAlarm()
{

	if(InteractionAlarmCompo)
	{
		UUserWidget* Widget = InteractionAlarmCompo->GetWidget();
		if (Widget)
		{
			InteractionAlarmCompo->GetWidget()->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}