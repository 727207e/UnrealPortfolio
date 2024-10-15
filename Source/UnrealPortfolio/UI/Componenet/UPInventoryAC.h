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

	// �������Ʈ���� ������ �Լ� ����
	UFUNCTION(BlueprintImplementableEvent, Category = "Inventory")
	void OpenInventory();

	//TODO : �������Ʈ�� ��ũ��Ʈ�� �̵��� �ڿ� �ش� ������ ������ ������ �ϰ�, �������� �������� ������ ��.(��ġ ����)
	UFUNCTION(BlueprintImplementableEvent, Category = "Inventory")
	void ItemGamePlayEffect(int Number);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UGameplayEffect> GetGameplayEffect;
};
