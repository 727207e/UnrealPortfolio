// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/GATA/GATA_RangeEnemeyFire.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

AGATA_RangeEnemeyFire::AGATA_RangeEnemeyFire()
{
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

void AGATA_RangeEnemeyFire::BeginPlay()
{
	Super::BeginPlay();

	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), MuzzleFX, GetActorLocation());
	MuzzleComponent->SetAsset(ProjectileFX);
}

