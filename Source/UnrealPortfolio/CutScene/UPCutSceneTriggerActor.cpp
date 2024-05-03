// Fill out your copyright notice in the Description page of Project Settings.


#include "CutScene/UPCutSceneTriggerActor.h"
#include "Components/BoxComponent.h"
#include "Camera/CameraComponent.h"
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
	
	AUPMainCharacter* MyCharacter = Cast<AUPMainCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (MyCharacter != OtherActor)
	{
		return;
	}

	bIsTriggerFirst = false;

	UCameraComponent* MainCamera = MyCharacter->GetCameraComponent();
	MainCamera->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	MainCamera->SetRelativeTransform(TargetCameraTrans->GetTransform());

	GetWorld()->GetTimerManager().SetTimer(CameraMoveTimerHandle, this, &AUPCutSceneTriggerActor::CameraMoveTimer, 0.1f, true);
}

void AUPCutSceneTriggerActor::CameraMoveTimer()
{
	UE_LOG(LogTemp, Error, TEXT("11111"));
}
