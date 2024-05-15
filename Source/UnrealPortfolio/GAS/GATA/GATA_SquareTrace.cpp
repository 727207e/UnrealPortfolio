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
#include "Components/DecalComponent.h"

AGATA_SquareTrace::AGATA_SquareTrace()
{
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	SetRootComponent(Box);
	Box->SetActive(false);

	SquareDecal = CreateDefaultSubobject<UDecalComponent>(TEXT("SquareDecal"));
	SquareDecal->SetupAttachment(RootComponent);
	SquareDecal->SetRelativeRotation(FRotator(0, -90.0f, 0.f));

	bReplicates = true;
	bIsDrawDecal = false;

	BoxSizeX = 0;
	BoxSizeY = 0;
	BoxSizeZ = 10000;

	DecalDelayTime = 1.3f;
	DestroyTATime = 0.3;
}

void AGATA_SquareTrace::ConfirmTargetingAndContinue()
{
	bDestroyOnConfirmation = false;

	GetAttributeSetting();
	InitSquareTrace();

	if (bIsDrawDecal)
	{
		DrawDecal();
	}
	else
	{
		StartTargeting();
	}
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

void AGATA_SquareTrace::DrawDecal()
{
	SquareDecal->DecalSize = Box->GetScaledBoxExtent();

	FTimerHandle StartTarget;
	GetWorld()->GetTimerManager().SetTimer(StartTarget, FTimerDelegate::CreateLambda([&]
		{
			SquareDecal->SetActive(false);
			StartTargeting();
		}), DecalDelayTime, false);
}

void AGATA_SquareTrace::GetAttributeSetting()
{
	BoxSizeX = CurrentData->TargetAttributeSet->GetAttackRadius();
	BoxSizeY = CurrentData->TargetAttributeSet->GetAttackRange();
}

void AGATA_SquareTrace::InitSquareTrace()
{
	ACharacter* SourceCharacter = CastChecked<ACharacter>(SourceActor);
	USkeletalMeshComponent* SkeletalMeshComponent = SourceCharacter->GetMesh();
	if (!SkeletalMeshComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("AGATA_SquareTrace : Skeletal mesh component not found."));
		return;
	}

	if (!SkeletalMeshComponent->DoesSocketExist(CurrentData->TargetGenName))
	{
		UE_LOG(LogTemp, Error, TEXT("AGATA_SquareTrace : Skeletal mesh component not found."));
		return;
	}
	FTransform CurrentBoxTransform = Box->GetComponentTransform();
	CurrentBoxTransform.SetScale3D(FVector(BoxSizeX, BoxSizeY, BoxSizeZ));
	Box->SetRelativeTransform(CurrentBoxTransform);

	FTransform CurrentTransform = GetActorTransform();
	CurrentTransform.SetLocation(SkeletalMeshComponent->GetSocketLocation(CurrentData->TargetGenName));
	CurrentTransform.SetRotation(SourceCharacter->GetActorQuat());

	SetActorTransform(CurrentTransform);
}

void AGATA_SquareTrace::StartTargeting()
{
	Box->OnComponentBeginOverlap.AddDynamic(this, &AGATA_SquareTrace::OnOverlapBegin);

	Box->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	FTimerHandle DeadTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(DeadTimerHandle, FTimerDelegate::CreateLambda([&]
		{
			Destroy();
		}), DestroyTATime, false);
}