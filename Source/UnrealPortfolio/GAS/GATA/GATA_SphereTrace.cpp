// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/GATA/GATA_SphereTrace.h"
#include "Abilities/GameplayAbility.h"
#include "Components/SphereComponent.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Components/SkeletalMeshComponent.h"
#include "GAS/Actor/GameplaySkillEventDataRequest.h"
#include "GAS/Attribute/BossDataSet/UPBossSkillAttributeSet.h"
#include "Character/UPMainCharacter.h"
#include "GameFramework/Character.h"
#include "Components/DecalComponent.h"
#include "Components/SceneComponent.h"
#include "defines/UPCollision.h"

AGATA_SphereTrace::AGATA_SphereTrace()
{
	USceneComponent* RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(RootComp);

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->SetupAttachment(RootComp);
	Sphere->SetActive(false);
	Sphere->SetCollisionProfileName(CPROFILE_UP_ENEMYATTACKRANGE);
	Sphere->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

	SphereDecal = CreateDefaultSubobject<UDecalComponent>(TEXT("SphereDecal"));
	SphereDecal->SetupAttachment(Sphere);

	bReplicates = true;
	bIsDrawDecal = false;

	SphereRadius = 20.0f;

	DecalDelayTime = 1.3f;
	DestroyTATime = 0.3f;
}

void AGATA_SphereTrace::ConfirmTargetingAndContinue()
{
	bDestroyOnConfirmation = false;

	GetAttributeSetting();
	InitTrace();

	if (bIsDrawDecal)
	{
		DrawDecal();
	}
	else
	{
		StartTargetingTrace();
	}
}

void AGATA_SphereTrace::Destroyed()
{
	Super::Destroyed();

	FGameplayAbilityTargetDataHandle DataHandle;
	TargetDataReadyDelegate.Broadcast(DataHandle);
}

void AGATA_SphereTrace::BeginPlay()
{
	Super::BeginPlay();
	Sphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AGATA_SphereTrace::OnOverlapBegin);
}

void AGATA_SphereTrace::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult)
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

void AGATA_SphereTrace::DrawDecal()
{
	FTimerHandle StartTarget;
	GetWorld()->GetTimerManager().SetTimer(StartTarget, FTimerDelegate::CreateLambda([&]
		{
			SphereDecal->SetVisibility(false);
			StartTargetingTrace();
		}), DecalDelayTime, false);
}

void AGATA_SphereTrace::GetAttributeSetting()
{
	SphereRadius = CurrentData->TargetAttributeSet->GetAttackRadius();
}

void AGATA_SphereTrace::StartTargetingTrace()
{
	Sphere->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	FTimerHandle DeadTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(DeadTimerHandle, FTimerDelegate::CreateLambda([&]
		{
			Destroy();
		}), DestroyTATime, false);
}

void AGATA_SphereTrace::InitTrace()
{
	ACharacter* SourceCharacter = CastChecked<ACharacter>(SourceActor);
	USkeletalMeshComponent* SkeletalMeshComponent = SourceCharacter->GetMesh();
	if (!SkeletalMeshComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("AGATA_SphereTrace : Skeletal mesh component not found."));
		return;
	}

	if (!SkeletalMeshComponent->DoesSocketExist(CurrentData->TargetGenName))
	{
		UE_LOG(LogTemp, Error, TEXT("AGATA_SphereTrace : Skeletal mesh component not found."));
		return;
	}
	FTransform CurrentBoxTransform = Sphere->GetRelativeTransform();
	Sphere->SetRelativeScale3D(FVector(SphereScale, SphereScale, SphereScale));

	FVector NewLocation = SkeletalMeshComponent->GetSocketLocation(CurrentData->TargetGenName);
	FRotator NewRotation = SourceCharacter->GetActorRotation();

	RootComponent->SetRelativeLocationAndRotation(NewLocation, NewRotation);
}
