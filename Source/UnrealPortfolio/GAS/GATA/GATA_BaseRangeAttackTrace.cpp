// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/GATA/GATA_BaseRangeAttackTrace.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/SphereComponent.h"
#include "GAS/Attribute/EntityAttributeSet.h"
#include "Character/UPBattleBaseCharacter.h"
#include "GameFramework/Character.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/CapsuleComponent.h"

AGATA_BaseRangeAttackTrace::AGATA_BaseRangeAttackTrace()
{
	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	Capsule->InitCapsuleSize(50.0f, 800.0f);
	SetRootComponent(Capsule);

	MuzzleFX = CreateDefaultSubobject<UNiagaraSystem>(TEXT("Muzzle"));
	ProjectileFX = CreateDefaultSubobject<UNiagaraSystem>(TEXT("ProjectileFX"));
	HitFX = CreateDefaultSubobject<UNiagaraSystem>(TEXT("HitFX"));

	ProjectTileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));

	MuzzleComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("MuzzleComponent"));
	MuzzleComponent->SetupAttachment(RootComponent);

	bReplicates = true;
}

void AGATA_BaseRangeAttackTrace::ConfirmTargetingAndContinue()
{
	bDestroyOnConfirmation = false;

	SettingProjectile();
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), MuzzleFX, GetActorLocation());
	MuzzleComponent->SetAsset(ProjectileFX);
	Capsule->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnOverlapBegin);

	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(SourceActor);
	if (nullptr == TargetASC)
	{
		UE_LOG(LogTemp, Error, TEXT("RangeAttackTrace Can't Find ASC"));
		return;
	}

	const UEntityAttributeSet* AttributeSet = TargetASC->GetSet<UEntityAttributeSet>();
	if (!AttributeSet)
	{
		UE_LOG(LogTemp, Error, TEXT("RangeAttackTrace Can't Find AttributeSet"));
		return;
	}

	FTimerHandle DeadTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(DeadTimerHandle, this, &ThisClass::AutoDestroy, AttributeSet->GetAttackRadius(), false);
}

void AGATA_BaseRangeAttackTrace::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult)
{
	const AUPBattleBaseCharacter* HitEnemyCharacter = Cast<AUPBattleBaseCharacter>(OtherActor);
	if (HitEnemyCharacter == nullptr)
	{
		return;
	}

	FGameplayAbilityTargetDataHandle DataHandle;

	FGameplayAbilityTargetData_SingleTargetHit* TargetData = new FGameplayAbilityTargetData_SingleTargetHit(SweepHitResult);
	DataHandle.Add(TargetData);
	TargetDataReadyDelegate.Broadcast(DataHandle);
	Destroyed();

	return;
}

void AGATA_BaseRangeAttackTrace::SettingProjectile()
{
	const ACharacter* SourceCharacter = CastChecked<ACharacter>(SourceActor);
	const USkeletalMeshComponent* SkeletalMeshComponent = SourceCharacter->GetMesh();
	if (!SkeletalMeshComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("RangeAttackTrace : Skeletal mesh component not found."));
		return;
	}

	if (!SkeletalMeshComponent->DoesSocketExist(SocketName))
	{
		UE_LOG(LogTemp, Error, TEXT("RangeAttackTrace : Skeletal mesh component not found."));
		return;
	}

	FTransform CurrentTransform = GetActorTransform();
	CurrentTransform.SetLocation(SkeletalMeshComponent->GetSocketLocation(SocketName));
	CurrentTransform.SetRotation(SourceCharacter->GetActorQuat());

	SetActorTransform(CurrentTransform);
}

void AGATA_BaseRangeAttackTrace::AutoDestroy()
{
	FGameplayAbilityTargetDataHandle DataHandle;
	TargetDataReadyDelegate.Broadcast(DataHandle);

	return;
}
