// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "UPBossRunDummyAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPORTFOLIO_API UUPBossRunDummyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public :
    UUPBossRunDummyAnimInstance();

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<class UAnimMontage*> AnimationArray;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
    int32 AnimIndex;

protected:
    virtual void NativeInitializeAnimation() override;
    
public :
    UFUNCTION(BlueprintCallable, Category = "Animation")
    void MontageFinish(UAnimMontage* Montage, bool bInterrupted);

private :
    ACharacter* BossDummy;

    float Velocity = 0.0f;
    void MontageSetting();
    void BossFlyUp();
    const FName FlyingName = "AM_BossFlying";
};
