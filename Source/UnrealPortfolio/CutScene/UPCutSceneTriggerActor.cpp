// Fill out your copyright notice in the Description page of Project Settings.


#include "CutScene/UPCutSceneTriggerActor.h"
#include "Components/BoxComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "defines/UPCollision.h"
#include "Character/UPMainCharacter.h"
#include "Curves/CurveFloat.h"

// Sets default values
AUPCutSceneTriggerActor::AUPCutSceneTriggerActor()
{
	BoxRoot = CreateDefaultSubobject<UBoxComponent>(TEXT("Root"));
	SetRootComponent(BoxRoot);
	BoxRoot->OnComponentBeginOverlap.AddDynamic(this, &AUPCutSceneTriggerActor::OnOverlapBegin);
	BoxRoot->SetWorldScale3D(FVector(15.0f, 15.0f, 15.0f));
	BoxRoot->SetCollisionProfileName(CPROFILE_UP_CUTSCENETRIGGER);

	bIsTriggerFirst = true;
	IndexCount = 0;
	CurTime = 0;
}

void AUPCutSceneTriggerActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult)
{
	if (!bIsTriggerFirst)
	{
		return;
	}

	if (CameraMoveEventArray.Num() == 0)
	{
		UE_LOG(LogTemp, Error, TEXT("UPCutSceneTriggerActor Doesn't Have CameraMoveEventArray"));
		return;
	}
	
	MyCharacter = Cast<AUPMainCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (MyCharacter != OtherActor)
	{
		return;
	}

	bIsTriggerFirst = false;

	StartCutScene();
}

void AUPCutSceneTriggerActor::StartCutScene()
{
	MainCamera = MyCharacter->GetCameraComponent();
	MainCamera->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	CameraMoveEvent = CameraMoveEventArray[IndexCount];

	if (CameraMoveEvent.StartType == EStartType::StartCamera)
	{
		StartTransform = MainCamera->GetComponentTransform();
	}
	else
	{
		StartTransform = CameraMoveEvent.StartCameraTrans->GetTransform();
	}

	DestinationTransform = CameraMoveEvent.DestinationCameraTrans->GetTransform();
	IndexCount++;

	GetWorld()->GetTimerManager().ClearTimer(CameraMoveTimerHandle);
	GetWorld()->GetTimerManager().SetTimer(CameraMoveTimerHandle, this, &AUPCutSceneTriggerActor::CameraMoveTimer, GetWorld()->DeltaTimeSeconds, true);
}

void AUPCutSceneTriggerActor::CameraMoveTimer()
{
	CurTime += GetWorld()->DeltaTimeSeconds;
	float TargetPoint = CameraMoveEvent.CurveData->GetFloatValue(CurTime/ CameraMoveEvent.PlayTime);

	FVector ResultLocation = FMath::Lerp(StartTransform.GetLocation(), DestinationTransform.GetLocation(), TargetPoint);
	MainCamera->SetWorldLocation(ResultLocation);

	FQuat ResultRotation = FMath::Lerp(StartTransform.GetRotation(), DestinationTransform.GetRotation(), TargetPoint);
	MainCamera->SetWorldRotation(ResultRotation);

	if (CurTime >= CameraMoveEvent.PlayTime)
	{
		CurTime = 0;
		GetWorld()->GetTimerManager().ClearTimer(CameraMoveTimerHandle);
		GetWorld()->GetTimerManager().SetTimer(CameraMoveTimerHandle, FTimerDelegate::CreateLambda([&]() {

			if (IndexCount >= CameraMoveEventArray.Num())
			{
				MyCharacter->SetCharacterControl(ECharacterControlType::TopDown);
			}
			else
			{
				StartCutScene();
			}
		}), 1.0f, false, CameraMoveEvent.StayTime);
	}
}