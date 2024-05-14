// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "AbilityTask_LookAtMouse.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FMouseDirectionDelegate,const FVector, TargetLocation);


UCLASS()
class UNREALPORTFOLIO_API UAbilityTask_LookAtMouse : public UAbilityTask
{
	GENERATED_BODY()
public:
	UAbilityTask_LookAtMouse();
	static UAbilityTask_LookAtMouse* CreateTask(UGameplayAbility* OwningAbility);
	virtual void Activate() override;
	void LookAtMouse();

	bool bIsDone;
};
