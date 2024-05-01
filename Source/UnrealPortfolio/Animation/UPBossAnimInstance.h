// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/UPEntityAnimInstance.h"
#include "UPBossAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPORTFOLIO_API UUPBossAnimInstance : public UUPEntityAnimInstance
{
	GENERATED_BODY()
	

protected:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
};
