// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/GATA/GATA_BossRangeMultiFire.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GAS/Actor/GameplaySkillEventDataRequest.h"
#include "Components/SphereComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

AGATA_BossRangeMultiFire::AGATA_BossRangeMultiFire()
{
	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> BossMultiMuzzleFXRef(TEXT("/Script/Niagara.NiagaraSystem'/Game/DownloadAssets/Pack_VFX/VFX_Niagara/Stylized_Projectiles/Muzzle/NS_Stylized_Projectiles_Muzzle13.NS_Stylized_Projectiles_Muzzle13'"));
	if (BossMultiMuzzleFXRef.Object)
	{
		MuzzleFX = BossMultiMuzzleFXRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> BossMultiProjectileFXRef(TEXT("/Script/Niagara.NiagaraSystem'/Game/DownloadAssets/Pack_VFX/VFX_Niagara/Stylized_Projectiles/Projectile/NS_Stylized_Projectiles_Projectile13.NS_Stylized_Projectiles_Projectile13'"));
	if (BossMultiProjectileFXRef.Object)
	{
		ProjectileFX = BossMultiProjectileFXRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> BossMultiHitFXRef(TEXT("/Script/Niagara.NiagaraSystem'/Game/DownloadAssets/Pack_VFX/VFX_Niagara/Stylized_Projectiles/Hit/NS_Stylized_Projectiles_Hit13.NS_Stylized_Projectiles_Hit13'"));
	if (BossMultiHitFXRef.Object)
	{
		HitFX = BossMultiHitFXRef.Object;
	}

	ProjectTileMovement->Velocity = FVector(0, 0, 0);
}

void AGATA_BossRangeMultiFire::ConfirmTargetingAndContinue()
{
	bDestroyOnConfirmation = false;
	InitializeSphere();
}

void AGATA_BossRangeMultiFire::InitializeSphere()
{
	for (int32 i = 0; i < 4; ++i)
	{
		AGATA_RangeEnemeyFire* SpawnedTargetActor = GetWorld()->SpawnActorDeferred<AGATA_RangeEnemeyFire>(AGATA_RangeEnemeyFire::StaticClass(), FTransform::Identity, nullptr, nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
		if (SpawnedTargetActor)
		{
			SpawnedTargetActor->SocketName = CurrentData->TargetGenName;
			SpawnedTargetActor->MuzzleFX = MuzzleFX;
			SpawnedTargetActor->ProjectileFX = ProjectileFX;
			SpawnedTargetActor->HitFX = HitFX;

			SpawnedTargetActor->SetShowDebug(true);
			SpawnedTargetActor->TargetDataReadyDelegate.AddUObject(this, &AGATA_BossRangeMultiFire::OnProjectileFindTarget);
			SpawnedTargetActor->FinishSpawning(SourceActor->GetActorTransform());
			SpawnedTargetActor->StartTargeting(OwningAbility);
			SpawnedTargetActor->ConfirmTargeting();
			SpawnedTargetActor->SetProjectileSpeed(3);
		}
	}
}

void AGATA_BossRangeMultiFire::OnProjectileFindTarget(const FGameplayAbilityTargetDataHandle& DataHandle)
{
	OnTargetDetect.Broadcast(DataHandle);
}
