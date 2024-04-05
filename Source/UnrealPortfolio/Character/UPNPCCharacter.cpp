// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/UPNPCCharacter.h"
#include "defines/UPCollision.h"
#include "Components/CapsuleComponent.h"
#include "Level/UPLevelScriptActor.h"
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
	InteractionAlarmCompo->GetWidget()->AddToViewport();
	HideInterAction();

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

	AUPLevelScriptActor* UpLevelScript = Cast<AUPLevelScriptActor>(GetWorld()->GetLevelScriptActor());
	if (UpLevelScript)
	{
		UE_LOG(LogTemp, Log, TEXT("ShowRaiderSelector22222"));
		UpLevelScript->LoadNextLevelByAsync(NextLevelPath);
	}

}

void AUPNPCCharacter::ShowInterAction()
{
	if(InteractionAlarmCompo)
	{
		InteractionAlarmCompo->GetWidget()->SetVisibility(ESlateVisibility::Visible);	
	}
}

void AUPNPCCharacter::HideInterAction()
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