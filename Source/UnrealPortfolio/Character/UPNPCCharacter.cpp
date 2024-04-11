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
	GetCapsuleComponent()->SetCollisionProfileName(CPROFILE_PAWN);
	
	// Mesh
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -100.0f), FRotator(0.0f, -90.0f, 0.0f));
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	GetMesh()->SetCollisionProfileName(CPROFILE_PAWN);

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
	
	InteractionAlarmCompo = CreateDefaultSubobject<UWidgetComponent>(TEXT("InterActionCompo"));
	InteractionAlarmCompo->SetupAttachment(GetMesh());			
	static ConstructorHelpers::FClassFinder<UUserWidget> InterActionClassRef(TEXT("/Game/UI/WBP_InteractionAlarm.WBP_InteractionAlarm_C"));
	if(InterActionClassRef.Class)
	{
		InteractionAlarmCompo->SetWidgetClass(InterActionClassRef.Class);
		InteractionAlarmCompo->SetWidgetSpace(EWidgetSpace::World);
		InteractionAlarmCompo->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	
	TakeUiActions.Add(FTakeWidgetDelegateWrapper(FOnShowNPCWidgetDelegate::CreateUObject(this,&AUPNPCCharacter::ShowWeaponShopWidget)));
	TakeUiActions.Add(FTakeWidgetDelegateWrapper(FOnShowNPCWidgetDelegate::CreateUObject(this,&AUPNPCCharacter::ShowItemShopWidget)));
	TakeUiActions.Add(FTakeWidgetDelegateWrapper(FOnShowNPCWidgetDelegate::CreateUObject(this,&AUPNPCCharacter::ShowRaiderSelector)));

	NPCCameraTransform = CreateDefaultSubobject<USceneComponent>(TEXT("CameraTransform"));
	NPCCameraTransform->SetupAttachment(RootComponent);

	GetCharacterMovement()->SetIsReplicated(false);
}

void AUPNPCCharacter::TakeNPCWidgetShow()
{
	UE_LOG(LogTemp,Log,TEXT("Show Type"));
	TakeUiActions[static_cast<uint8>(widgetType)].OnTakeWidget.ExecuteIfBound();
}

void AUPNPCCharacter::TakeNPCWidgetHide()
{
	UE_LOG(LogTemp,Log,TEXT("Hide Type"));
	TakeUiActions[static_cast<uint8>(widgetType)].OnTakeWidget.ExecuteIfBound();
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
	//
	// AUPLevelScriptActor* UpLevelScript = Cast<AUPLevelScriptActor>(GetWorld()->GetLevelScriptActor());
	// if (UpLevelScript)
	// {
	// 	UE_LOG(LogTemp, Log, TEXT("ShowRaiderSelector22222"));
	// 	UpLevelScript->LoadNextLevelByAsync(NextLevelPath);
	// }

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