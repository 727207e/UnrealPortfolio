// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/UPEntityAnimInstance.h"
#include "UPEnemyAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPORTFOLIO_API UUPEnemyAnimInstance : public UUPEntityAnimInstance
{
	GENERATED_BODY()
	
public :
	UUPEnemyAnimInstance();

protected:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
	uint8 bIsTargetFound : 1;

	//if Target Die, Reset Searching
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
	uint8 bIsTargetLock : 1;

public :
	void SetIsTargetLock(bool IsLockOn);
};
