// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/DataAsset/MainCharacter/UPMainCharacterClassTable.h"
#include "UPGameSingleton.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPORTFOLIO_API UUPGameSingleton : public UObject
{
	GENERATED_BODY()
public:
	UUPGameSingleton();
	static UUPGameSingleton& Get();

	UPROPERTY(EditAnywhere, Category = TableData)
	int32 CurrentMainCharacterId;
		
	UPROPERTY(EditAnywhere, Category = TableData)
	TObjectPtr<UDataTable> ActionDataTable;

	UPROPERTY(EditAnywhere, Category = TableData)
	TObjectPtr<UDataTable> MainCharacterTable;
	
	TArray<FUPMainCharacterClassTable> MainCharacterArray;	

	FORCEINLINE FUPMainCharacterClassTable GetCharacterData(int32 InLevel) const
	{
		if (MainCharacterArray.IsValidIndex(InLevel))
			return MainCharacterArray[InLevel];
		else
			return FUPMainCharacterClassTable();
	}
	
	FORCEINLINE FUPMainCharacterClassTable GetCurrentMainCharacterData() const
	{
		return  MainCharacterArray[CurrentMainCharacterId];
	}
	
};
