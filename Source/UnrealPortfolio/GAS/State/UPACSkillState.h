// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UPACSkillState.generated.h"


UCLASS(Blueprintable)
class UNREALPORTFOLIO_API UUPACSkillState : public UActorComponent
{
	GENERATED_BODY()

public:	
	UUPACSkillState();

public :
	virtual void InitSkillState(AActor* Owner, TSubclassOf<class UUPBossSkillAttributeSet> AttributeSetType);
	virtual void PostInitialize(int32 CurPhaseNumber);


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class UUPBossSkillAttributeSet> AttributeSet;
};
