// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "Data/DataAsset/Item/UPWeaponTable.h"
#include "NiagaraComponent.h"
#include "StaticMeshWeaponComponent.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPORTFOLIO_API UStaticMeshWeaponComponent : public UStaticMeshComponent
{
	GENERATED_BODY()

	UStaticMeshWeaponComponent();
private:
	UPROPERTY();
	int32 WeaponId;
public:	
	UPROPERTY();
	int32 Grade;
	UPROPERTY();
	int32 WeaponLevel;
	UPROPERTY();
	int32 LegendSkillIndex;

	
	void BeginPlay() override;
	void SetWeaponData(const FUPWeaponTable& Model);
	void SetWeaponId(int32 TargetId);
	int32 GetWeaponId() const;
	void Hidden();
	
	FName NiagaraParent;
	UPROPERTY(EditAnywhere ,Category = "Weapon")
	TObjectPtr<UNiagaraComponent> WeaponTrail;
	
};
