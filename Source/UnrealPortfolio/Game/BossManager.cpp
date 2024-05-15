// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/BossManager.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "CutScene/UPCutSceneTriggerActor.h"
#include "Components/SceneComponent.h"
#include "Game/UPGameInstance.h"

// Sets default values
ABossManager::ABossManager()
{
	StrugglePatern = {1, 2, 3, 2, 4, 5, 6, 7};
}

void ABossManager::GenBoss()
{
	Boss = GetWorld()->SpawnActor<ACharacter>(BossBody, GenPosition->GetActorLocation(), GenPosition->GetActorRotation());

}

void ABossManager::BeginPlay()
{
	UUPGameInstance* UPGameInstance = Cast<UUPGameInstance>(GetGameInstance());

	if (UPGameInstance)
	{
		UPGameInstance->SetBossManager(this);
	}

	if (CutSceneTrigger)
	{
		CutSceneTrigger->OnCutSceneEnd.AddUObject(this, &ABossManager::StartStruggling);
	}

	SpawnActorsAroundCenter(GenPosition->GetActorLocation());
}

void ABossManager::StartStruggling()
{	
	if (StruggleBossDummy)
	{
		ACharacter* struggle = Cast<ACharacter>(GetWorld()->SpawnActor(StruggleBossDummy));
		if (struggle)
		{
			struggle->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
		}
	}
}

FTransform ABossManager::GetRandomAroundTransform()
{
	if (AroundActors.Num() > 0)
	{
		int32 RandomIndex = FMath::RandRange(0, AroundActors.Num() - 1);
		return AroundActors[RandomIndex]->GetActorTransform();
	}
	return FTransform();
}

void ABossManager::SpawnActorsAroundCenter(const FVector& Center)
{
	TArray<FVector> Positions = CalculatePositionsAroundCenter(Center);
	for (const FVector& Position : Positions)
	{
		AActor* NewActor = GetWorld()->SpawnActor<AActor>(AActor::StaticClass());
		if (NewActor)
		{
			USceneComponent* SceneComponent = NewObject<USceneComponent>(NewActor, USceneComponent::StaticClass(), TEXT("RootSceneComponent"));
			if (SceneComponent)
			{
				NewActor->SetRootComponent(SceneComponent);
				SceneComponent->RegisterComponent();
				FVector DirectionToCenter = (Center - Position).GetSafeNormal();
				FRotator NewRotation = DirectionToCenter.Rotation();
				NewActor->SetActorRotation(NewRotation);
				NewActor->SetActorLocation(Position);

				AroundActors.Add(NewActor);
			}
		}
	}
}

TArray<FVector> ABossManager::CalculatePositionsAroundCenter(const FVector& Center)
{
	TArray<FVector> Positions;
	const int32 NumPositions = 8;
	const float AngleIncrement = 360.0f / NumPositions;

	for (int32 i = 0; i < NumPositions; ++i)
	{
		float Angle = FMath::DegreesToRadians(i * AngleIncrement);
		FVector Offset = FVector(FMath::Cos(Angle) * Radius, FMath::Sin(Angle) * Radius, ZOffset);
		FVector Position = Center + Offset;
		Positions.Add(Position);
	}

	return Positions;
}
