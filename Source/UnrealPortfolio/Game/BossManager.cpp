// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/BossManager.h"
#include "Character/UPStrugglingBoss.h"
#include "Character/UPBossCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "CutScene/UPCutSceneTriggerActor.h"
#include "Components/SceneComponent.h"
#include "GAS/Attribute/EntityAttributeSet.h"
#include "Game/UPGameInstance.h"

ABossManager::ABossManager()
{
}

void ABossManager::PreInitializeComponents()
{
	Super::PreInitializeComponents();

	UUPGameInstance* UPGameInstance = Cast<UUPGameInstance>(GetGameInstance());

	if (UPGameInstance)
	{
		UPGameInstance->SetBossManager(this);
	}
}

void ABossManager::GenBoss()
{
	ACharacter* SpawnBoss = GetWorld()->SpawnActor<ACharacter>(BossBody, GenPosition->GetActorLocation(), GenPosition->GetActorRotation());
	Boss = Cast<AUPBossCharacter>(SpawnBoss);

	if (nullptr == Boss)
	{
		UE_LOG(LogTemp, Error, TEXT("BossManager : The Spawn Boss is Not UPBossCharacter"));
		return;
	}

	Boss->UpdatePhaseNumber(BossPhaseNumber);
	Boss->OnHitDelegate.AddUObject(this, &ABossManager::BossHPTriggerCheck);

	if (BossStartingHP > 0 && HasAuthority())
	{
		const_cast<UEntityAttributeSet*>(Boss->GetAbilitySystemComponent()->GetSet<UEntityAttributeSet>())->SetHpValue(BossStartingHP);
	}
}

void ABossManager::BeginPlay()
{
	Super::BeginPlay();

	if (CutSceneTrigger)
	{
		CutSceneTrigger->OnCutSceneEnd.AddUObject(this, &ABossManager::StartStruggling);
	}

	SpawnActorsAroundCenter(GenPosition->GetActorLocation());

	if (bIsSpawnImmediately && HasAuthority())
	{
		FTimerHandle BossGenTimeHandle;
		GetWorld()->GetTimerManager().SetTimer(BossGenTimeHandle, this, &ABossManager::GenBoss, 2.0f, false);
	}
}

void ABossManager::StartStruggling()
{	
	if (StruggleBossDummy)
	{
		AUPStrugglingBoss* struggle = Cast<AUPStrugglingBoss>(GetWorld()->SpawnActor(StruggleBossDummy));
		if (struggle)
		{
			struggle->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
			struggle->StartPatern();
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

void ABossManager::BossHPTriggerCheck()
{
	float CurBossHp = Boss->GetAbilitySystemComponent()->GetSet<UEntityAttributeSet>()->GetHp();

	for (int32 index = 0; index < BossTriggers.Num(); ++index)
	{
		if (CurBossHp <= BossTriggers[index].BossTriggerHp)
		{
			BossTriggers[index].CutSceneTrigger->ExecuteEvent();
			BossTriggers.RemoveAt(index);
			break;
		}
	}
}

void ABossManager::BossDestroy()
{
	Boss->Destroy();
	Boss = nullptr;
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
