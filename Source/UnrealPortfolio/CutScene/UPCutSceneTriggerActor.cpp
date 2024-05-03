// Fill out your copyright notice in the Description page of Project Settings.


#include "CutScene/UPCutSceneTriggerActor.h"
#include "Components/BoxComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "defines/UPCollision.h"
#include "Character/UPMainCharacter.h"

// Sets default values
AUPCutSceneTriggerActor::AUPCutSceneTriggerActor()
{
	BoxRoot = CreateDefaultSubobject<UBoxComponent>(TEXT("Root"));
	SetRootComponent(BoxRoot);
	BoxRoot->OnComponentBeginOverlap.AddDynamic(this, &AUPCutSceneTriggerActor::OnOverlapBegin);
	BoxRoot->SetWorldScale3D(FVector(15.0f, 15.0f, 15.0f));
	BoxRoot->SetCollisionProfileName(CPROFILE_UP_CUTSCENETRIGGER);

	bIsTriggerFirst = true;
	MoveLimitTime = 5.0f;
	StayLimitTime = 2.0f;
	ReturnLimitTime = 1.0f;
}

void AUPCutSceneTriggerActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult)
{
	if (!bIsTriggerFirst)
	{
		return;
	}

	if (nullptr == TargetCameraTrans)
	{
		UE_LOG(LogTemp, Error, TEXT("UPCutSceneTriggerActor Doesn't Have TargetCameraTrans"));
		return;
	}
	
	MyCharacter = Cast<AUPMainCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (MyCharacter != OtherActor)
	{
		return;
	}

	bIsTriggerFirst = false;

	MainCamera = MyCharacter->GetCameraComponent();
	MainCamera->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	StartTransform = MainCamera->GetComponentTransform();
	TargetTransform = TargetCameraTrans->GetTransform();

	GetWorld()->GetTimerManager().SetTimer(CameraMoveTimerHandle, this, &AUPCutSceneTriggerActor::CameraMoveTimer, GetWorld()->DeltaTimeSeconds, true);
}

void AUPCutSceneTriggerActor::CameraMoveTimer()
{
	CurTime += GetWorld()->DeltaTimeSeconds;
	FVector ResultLocation = FMath::Lerp(StartTransform.GetLocation(), TargetTransform.GetLocation(), CurTime / MoveLimitTime);
	MainCamera->SetWorldLocation(ResultLocation);

	FQuat ResultRotation = FMath::Lerp(StartTransform.GetRotation(), TargetTransform.GetRotation(), CurTime / MoveLimitTime);
	MainCamera->SetWorldRotation(ResultRotation);

	if (CurTime >= MoveLimitTime)
	{
		CurTime = 0;
		GetWorld()->GetTimerManager().ClearTimer(CameraMoveTimerHandle);

		GetWorld()->GetTimerManager().SetTimer(CameraMoveTimerHandle, FTimerDelegate::CreateLambda([&]() {
				MyCharacter->SetCharacterControl(ECharacterControlType::TopDown);
			}), StayLimitTime, false);
	}
}
