// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/GATA/GATA_BaseRangeAttackTrace.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/SphereComponent.h"
#include "Data/DataAttributeSet/EntityAttributeSet.h"
#include "GameFramework/Character.h"
#include "GameFramework/ProjectileMovementComponent.h"

AGATA_BaseRangeAttackTrace::AGATA_BaseRangeAttackTrace()
{
	SocketName = "Hand_r";

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

	bReplicates = true;
	
}

void AGATA_BaseRangeAttackTrace::ConfirmTargetingAndContinue()
{
	bDestroyOnConfirmation = false;

	SettingProjectile();
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), MuzzleFX, GetActorLocation());
	MuzzleComponent->SetAsset(ProjectileFX);
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnOverlapBegin);

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

void AGATA_BaseRangeAttackTrace::Destroyed()
{
	Super::Destroyed();
}

void AGATA_BaseRangeAttackTrace::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                                UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult)
{
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
