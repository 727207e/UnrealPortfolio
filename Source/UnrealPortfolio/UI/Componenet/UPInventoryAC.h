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

	//TODO : 블루프린트를 스크립트로 이동한 뒤에 해당 내용을 데이터 폼으로 하고, 가져오는 로직으로 수정할 것.(수치 포함)
	UFUNCTION(BlueprintImplementableEvent, Category = "Inventory")
	void ItemGamePlayEffect(int Number);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UGameplayEffect> GetGameplayEffect;
};
