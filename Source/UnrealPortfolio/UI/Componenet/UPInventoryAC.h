// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UPInventoryAC.generated.h"


UCLASS(Blueprintable)
class UNREALPORTFOLIO_API UUPInventoryAC : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UUPInventoryAC();

	// 블루프린트에서 구현할 함수 선언
	UFUNCTION(BlueprintImplementableEvent, Category = "Inventory")
	void OpenInventory();
};
