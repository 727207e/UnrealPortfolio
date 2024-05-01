// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/GATA/GATA_RangeEnemeyFire.h"
#include "NiagaraFunctionLibrary.h"
#include "Abilities/GameplayAbility.h"
#include "NiagaraComponent.h"
#include "Components/SphereComponent.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Character/UPMainCharacter.h"
#include "Data/DataAttributeSet/EntityAttributeSet.h"

AGATA_RangeEnemeyFire::AGATA_RangeEnemeyFire()
{
	SocketName = "FirePos";

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	SetRootComponent(Sphere);

	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> MuzzleFXRef(TEXT("/Script/Niagara.NiagaraSystem'/Game/DownloadAssets/Pack_VFX/VFX_Niagara/Stylized_Projectiles/Muzzle/NS_Stylized_Projectiles_Muzzle17.NS_Stylized_Projectiles_Muzzle17'"));
	if (MuzzleFXRef.Object)
	{
		MuzzleFX = MuzzleFXRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> ProjectileFXRef(TEXT("/Script/Niagara.NiagaraSystem'/Game/DownloadAssets/Pack_VFX/VFX_Niagara/Stylized_Projectiles/Projectile/NS_Stylized_Projectiles_Projectile17.NS_Stylized_Projectiles_Projectile17'"));
	if (ProjectileFXRef.Object)
	{
		ProjectileFX = ProjectileFXRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> HitFXRef(TEXT("/Script/Niagara.NiagaraSystem'/Game/DownloadAssets/Pack_VFX/VFX_Niagara/Stylized_Projectiles/Hit/NS_Stylized_Projectiles_Hit17.NS_Stylized_Projectiles_Hit17'"));
	if (HitFXRef.Object)
	{
		HitFX = HitFXRef.Object;
	}

	ProjectTileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectTileMovement->InitialSpeed = 1000;
	ProjectTileMovement->MaxSpeed = 1000;
	ProjectTileMovement->bShouldBounce = true;
	ProjectTileMovement->ProjectileGravityScale = 0;
	ProjectTileMovement->Velocity = FVector(1000, 0, 0);

	MuzzleComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("MuzzleComponent"));
	MuzzleComponent->SetupAttachment(RootComponent);

	SetReplicates(true);
	SetReplicateMovement(true);
}

void AGATA_RangeEnemeyFire::ConfirmTargetingAndContinue()
{
	bDestroyOnConfirmation = false;

	SettingProjectile();
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), MuzzleFX, GetActorLocation());
	MuzzleComponent->SetAsset(ProjectileFX);
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AGATA_RangeEnemeyFire::OnOverlapBegin);

	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(SourceActor);
	if (nullptr == TargetASC)
	{
		UE_LOG(LogTemp, Error, TEXT("GATA_RangeEnemyFire Can't Find ASC"));
		return;
	}

	const UEntityAttributeSet* AttributeSet = TargetASC->GetSet<UEntityAttributeSet>();
	if (!AttributeSet)
	{
		UE_LOG(LogTemp, Error, TEXT("GATA_RangeEnemyFire Can't Find AttributeSet"));
		return;
	}

	FTimerHandle DeadTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(DeadTimerHandle, this, &AGATA_RangeEnemeyFire::AutoDestroy, AttributeSet->GetAttackRadius(), false);
}

void AGATA_RangeEnemeyFire::Destroyed()
{
	Super::Destroyed();

	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), HitFX, GetActorLocation());
	MuzzleComponent->SetAsset(ProjectileFX);
}

void AGATA_RangeEnemeyFire::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult)
{
	AUPMainCharacter* MainCharacter = Cast<AUPMainCharacter>(OtherActor);
	if (MainCharacter == nullptr)
	{
		return;
	}

	FGameplayAbilityTargetDataHandle DataHandle;

	FGameplayAbilityTargetData_SingleTargetHit* TargetData = new FGameplayAbilityTargetData_SingleTargetHit(SweepHitResult);
	DataHandle.Add(TargetData);
	TargetDataReadyDelegate.Broadcast(DataHandle);
	return;
}

void AGATA_RangeEnemeyFire::SettingProjectile()
{
	ACharacter* SourceCharacter = CastChecked<ACharacter>(SourceActor);
	USkeletalMeshComponent* SkeletalMeshComponent = SourceCharacter->GetMesh();
	if (!SkeletalMeshComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("GATA_RangeEnemyFire : Skeletal mesh component not found."));
		return;
	}

	if (!SkeletalMeshComponent->DoesSocketExist(SocketName))
	{
		UE_LOG(LogTemp, Error, TEXT("GATA_RangeEnemyFire : Skeletal mesh component not found."));
		return;
	}

	FTransform CurrentTransform = GetActorTransform();
	CurrentTransform.SetLocation(SkeletalMeshComponent->GetSocketLocation(SocketName));
	CurrentTransform.SetRotation(SourceCharacter->GetActorQuat());

	SetActorTransform(CurrentTransform);
}

void AGATA_RangeEnemeyFire::AutoDestroy()
{
	FGameplayAbilityTargetDataHandle DataHandle;
	TargetDataReadyDelegate.Broadcast(DataHandle);

	return;
}


