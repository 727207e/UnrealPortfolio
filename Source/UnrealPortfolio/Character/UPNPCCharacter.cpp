// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/UPNPCCharacter.h"

#include "Animation/AnimClassData.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AUPNPCCharacter::AUPNPCCharacter()
{
	// Pawn
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	//GetCapsuleComponent()->SetCollisionProfileName(프로파일);

	// Movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// Mesh
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -100.0f), FRotator(0.0f, -90.0f, 0.0f));
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	GetMesh()->SetCollisionProfileName(TEXT("Pawn"));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> CharacterMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/OtherCharacterPack/Mesh/Dwarf_Mesh.Dwarf_Mesh'"));
	if (CharacterMeshRef.Object)
	{
		GetMesh()->SetSkeletalMesh(CharacterMeshRef.Object);
	}

	static ConstructorHelpers::FClassFinder<UAnimInstance> CharacterAnimRef(TEXT("/Game/OtherCharacterPack/Animations/ABP_Dwarf.ABP_Dwarf_C"));

	if(CharacterAnimRef.Class)
	{
		GetMesh()->SetAnimInstanceClass(CharacterAnimRef.Class);
	}

	TakeUiActions.Add(FTakeWidgetDelegateWrapper(FOnShowNPCWidgetDelegate::CreateUObject(this,&AUPNPCCharacter::ShowWeaponShopWidget)));
	TakeUiActions.Add(FTakeWidgetDelegateWrapper(FOnShowNPCWidgetDelegate::CreateUObject(this,&AUPNPCCharacter::ShowItemShopWidget)));
	TakeUiActions.Add(FTakeWidgetDelegateWrapper(FOnShowNPCWidgetDelegate::CreateUObject(this,&AUPNPCCharacter::ShowRaiderSelector)));
}

void AUPNPCCharacter::TakeNPCWidget()
{
	TakeUiActions[static_cast<uint8>(widgetType)].OnTakeWidget.ExecuteIfBound();
}

void AUPNPCCharacter::BeginPlay()
{
	Super::BeginPlay();
	TakeNPCWidget();
	
}

void AUPNPCCharacter::ShowWeaponShopWidget()
{
	UE_LOG(LogTemp,Log,TEXT("ShowWeaponShopWidget"));
}

void AUPNPCCharacter::ShowItemShopWidget()
{
	UE_LOG(LogTemp,Log,TEXT("ShowItemShopWidget"));
}

void AUPNPCCharacter::ShowRaiderSelector()
{
	UE_LOG(LogTemp,Log,TEXT("ShowRaiderSelector"));
}
