// Fill out your copyright notice in the Description page of Project Settings.


#include "Level/UPMoveNextLevelActor.h"
#include "Components/BoxComponent.h"
#include "Game/BossManager.h"
#include "Game/UPGameState.h"
#include "Character/UPMainCharacter.h"
#include "defines/UPCollision.h"

AUPMoveNextLevelActor::AUPMoveNextLevelActor()
{
	BoxRoot = CreateDefaultSubobject<UBoxComponent>(TEXT("Root"));
	SetRootComponent(BoxRoot);
	BoxRoot->SetWorldScale3D(FVector(15.0f, 15.0f, 15.0f));
	BoxRoot->SetCollisionProfileName(CPROFILE_UP_CUTSCENETRIGGER);

}

void AUPMoveNextLevelActor::BeginPlay()
{
	Super::BeginPlay();
	
	BoxRoot->OnComponentBeginOverlap.AddDynamic(this, &AUPMoveNextLevelActor::OnOverlapBegin);
}

void AUPMoveNextLevelActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult)
{
	if (TargetBossManager)
	{
		if (TargetBossManager->bIsBossDie != 1)
		{
			UE_LOG(LogTemp, Log, TEXT("AUPMoveNextLevelActor : Boss is Not Die Yet"));
			return;
		}
	}

	MoveNextLevel();
}

void AUPMoveNextLevelActor::MoveNextLevel()
{
	AUPGameState* UPGameState = Cast<AUPGameState>(GetWorld()->GetGameState());
	if (nullptr == UPGameState)
	{
		UE_LOG(LogTemp, Error, TEXT("AUPMoveNextLevelActor : Can't Find UPGameState"));
		return;
	}

	FString TargetLevelName = "/Game/Level/Dungeon/" + TargetNextLevel;
	UPGameState->MoveNextLevel(TargetLevelName);
}