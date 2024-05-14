// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/GATA/GATA_BossRangeMultiFire.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GAS/Actor/GameplaySkillEventDataRequest.h"
#include "Components/SphereComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "GameFramework/Character.h"
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
	AttackNumber = 4;
	PerProjectileDistance = 300;
}

void AGATA_BossRangeMultiFire::ConfirmTargetingAndContinue()
{
	bDestroyOnConfirmation = false;
	InitializeSphere();
}

void AGATA_BossRangeMultiFire::InitializeSphere()
{
	for (int32 index = 0; index < AttackNumber; ++index)
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
			SpawnedTargetActor->bIsSettingInSocket = false;
			SpawnedTargetActor->FinishSpawning(SourceActor->GetActorTransform());
			SpawnedTargetActor->StartTargeting(OwningAbility);
			SpawnedTargetActor->SetActorTransform(GetProjecttilePos(index));
			SpawnedTargetActor->SetProjectileSpeed(3);
			SpawnedTargetActor->ConfirmTargeting();
		}
	}
}
//0, 1, 2, 3
FTransform AGATA_BossRangeMultiFire::GetProjecttilePos(int index)
{
	ACharacter* SourceCharacter = CastChecked<ACharacter>(SourceActor);
	USkeletalMeshComponent* SkeletalMeshComponent = SourceCharacter->GetMesh();
	if (!SkeletalMeshComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("AGATA_BossRangeMultiFire : Skeletal mesh component not found."));
		return FTransform();
	}

	if (!SkeletalMeshComponent->DoesSocketExist(CurrentData->TargetGenName))
	{
		UE_LOG(LogTemp, Error, TEXT("AGATA_BossRangeMultiFire : Skeletal mesh component not found."));
		return FTransform();
	}

	FVector OriginPos = SkeletalMeshComponent->GetSocketLocation(CurrentData->TargetGenName);

	FVector RightVector = FVector::CrossProduct(FVector(0, 0, 1), SourceCharacter->GetActorForwardVector());
	RightVector.Normalize();

	int PositioningNumber = AttackNumber/2 > index ? index - 2 : index - 1;

	FTransform CurrentTransform = GetActorTransform();
	CurrentTransform.SetLocation(OriginPos + RightVector * PositioningNumber * PerProjectileDistance);
	CurrentTransform.SetRotation(CastChecked<ACharacter>(SourceActor)->GetActorQuat());

	return CurrentTransform;
}


void AGATA_BossRangeMultiFire::OnProjectileFindTarget(const FGameplayAbilityTargetDataHandle& DataHandle)
{
	OnTargetDetect.Broadcast(DataHandle);
}