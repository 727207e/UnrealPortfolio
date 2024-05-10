// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/GATA/GATA_SquareTrace.h"
#include "Abilities/GameplayAbility.h"
#include "Components/BoxComponent.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Components/SkeletalMeshComponent.h"
#include "GAS/Actor/GameplaySkillEventDataRequest.h"
#include "Data/DataAttributeSet/BossDataSet/UPBossSkillAttributeSet.h"
#include "Character/UPMainCharacter.h"
#include "GameFramework/Character.h"

AGATA_SquareTrace::AGATA_SquareTrace()
{
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	SetRootComponent(Box);
	Box->SetActive(false);

	bReplicates = true;
}

void AGATA_SquareTrace::ConfirmTargetingAndContinue()
{
	bDestroyOnConfirmation = false;

	InitSquareTrace();
}

void AGATA_SquareTrace::Destroyed()
{
	Super::Destroyed();

	FGameplayAbilityTargetDataHandle DataHandle;
	TargetDataReadyDelegate.Broadcast(DataHandle);
}

void AGATA_SquareTrace::BeginPlay()
{
	Super::BeginPlay();
	Box->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AGATA_SquareTrace::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult)
{
	AUPMainCharacter* MainCharacter = Cast<AUPMainCharacter>(OtherActor);
	if (MainCharacter == nullptr)
	{
		return;
	}

	FGameplayAbilityTargetDataHandle DataHandle;

	FHitResult Hit = FHitResult(SweepHitResult);
	Hit.HitObjectHandle = FActorInstanceHandle(OtherActor);

	FGameplayAbilityTargetData_SingleTargetHit* TargetData = new FGameplayAbilityTargetData_SingleTargetHit(Hit);
	DataHandle.Add(TargetData);
	OnTargetDetect.Broadcast(DataHandle);

	return;
}

void AGATA_SquareTrace::InitSquareTrace()
{
	ACharacter* SourceCharacter = CastChecked<ACharacter>(SourceActor);
	USkeletalMeshComponent* SkeletalMeshComponent = SourceCharacter->GetMesh();
	if (!SkeletalMeshComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("GATA_RangeEnemyFire : Skeletal mesh component not found."));
		return;
	}

	if (!SkeletalMeshComponent->DoesSocketExist(CurrentData->TargetGenName))
	{
		UE_LOG(LogTemp, Error, TEXT("GATA_RangeEnemyFire : Skeletal mesh component not found."));
		return;
	}
	FTransform CurrentBoxTransform = Box->GetComponentTransform();
	CurrentBoxTransform.SetScale3D(FVector(CurrentData->TargetAttributeSet->GetAttackRadius(), CurrentData->TargetAttributeSet->GetAttackRange(), 10000.0f));
	Box->SetRelativeTransform(CurrentBoxTransform);

	FTransform CurrentTransform = GetActorTransform();
	CurrentTransform.SetLocation(SkeletalMeshComponent->GetSocketLocation(CurrentData->TargetGenName));
	CurrentTransform.SetRotation(SourceCharacter->GetActorQuat());

	SetActorTransform(CurrentTransform);

	Box->OnComponentBeginOverlap.AddDynamic(this, &AGATA_SquareTrace::OnOverlapBegin);

	Box->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	FTimerHandle DeadTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(DeadTimerHandle, FTimerDelegate::CreateLambda([&]
		{
			Destroy();
		}), 0.3f, false);
}