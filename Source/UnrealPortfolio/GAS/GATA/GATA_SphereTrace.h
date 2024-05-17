// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAS/GATA/GATA_SkillTrace.h"
#include "GATA_SphereTrace.generated.h"

/**
 *  //Refactoring Require : SphereTrace And SqaureTrace 
 */
UCLASS()
class UNREALPORTFOLIO_API AGATA_SphereTrace : public AGATA_SkillTrace
{
	GENERATED_BODY()
	
public:
	AGATA_SphereTrace();

public:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class USphereComponent> Sphere;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class UDecalComponent> SphereDecal;

public:
	virtual void ConfirmTargetingAndContinue() override;
	virtual void Destroyed() override;
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult);

	virtual void DrawDecal() override;

protected:
	virtual void GetAttributeSetting();
	virtual void StartTargetingTrace();
	virtual	void InitTrace();

	float SphereRadius;
	float SphereScale;

	float DecalDelayTime = 0;
	float DestroyTATime = 0;
};