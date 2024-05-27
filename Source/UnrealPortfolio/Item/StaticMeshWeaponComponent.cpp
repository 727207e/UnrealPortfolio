// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/StaticMeshWeaponComponent.h"

#include "NiagaraComponent.h"

UStaticMeshWeaponComponent::UStaticMeshWeaponComponent()
{
	// const ConstructorHelpers::FObjectFinder<UNiagaraSystem> NiagaraSystemRef(TEXT("/Script/Niagara.NiagaraSystem'/Game/DownloadAssets/SlashHitVFX/NS/NS_Trail_Halberd.NS_Trail_Halberd'"));
	// if(NiagaraSystemRef.Object)
	// {
	// 	WeaponTrail = CreateDefaultSubobject<UNiagaraComponent>(TEXT("WeaponTrail"));
	// 	WeaponTrail->SetupAttachment(GetAttachmentRoot(),NiagaraParent);
	// 	WeaponTrail->SetAsset(NiagaraSystemRef.Object);
	// }

	Grade = -1;
	SetCollisionEnabled(ECollisionEnabled::NoCollision);
	const ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMeshRef(TEXT("/Script/Engine.StaticMesh'/Game/DownloadAssets/Primitive_Characters_Pack/Mesh/Primitive_02/Mesh_Weapons/SM_Primitive_02_Weapons_02.SM_Primitive_02_Weapons_02'"));
	if(StaticMeshRef.Object)
	{
		UStaticMeshComponent::SetStaticMesh(StaticMeshRef.Object);
	}
	WeaponLevel = 1;
	LegendSkillIndex = 0;
}

void UStaticMeshWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UStaticMeshWeaponComponent::SetWeaponData(const FUPWeaponTable& Model)
{
	SetStaticMesh(Model.Mesh);
	this->WeaponLevel = Model.WeaponLevel;
	this->Grade = Model.Grade;
	this->LegendSkillIndex = Model.LegendLevel;
}

void UStaticMeshWeaponComponent::SetWeaponId(int32 TargetId)
{
	this->WeaponId= TargetId;
}

int32 UStaticMeshWeaponComponent::GetWeaponId() const
{
	return  this->WeaponId;
}

void UStaticMeshWeaponComponent::Hidden()
{
	SetVisibility(false);
}
