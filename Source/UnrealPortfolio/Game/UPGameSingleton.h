// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/UPSkillData.h"
#include "Data/DataAsset/Item/UPWeaponTable.h"
#include "Data/DataAsset/MainCharacter/UPMainCharacterClassTable.h"
#include "Data/DataTable/Widget/ProgressWidgetModelData.h"
#include "Data/DataTable/Widget/SlotWidgetModelData.h"
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
	
	TArray<FUPMainCharacterClassTable> MainCharacterArray;
	TArray<FSlotWidgetModelData> SlotWidgetModelDataArray;
	TArray<FProgressWidgetModelData> ProgressWidgetModelDataArray;
	TArray<FUPSkillData> SkillDataArray;
	TArray<FUPWeaponTable> WeaponTablesArray;

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
	template<typename T>
	void LoadDataTableToArray(const FString& DataTablePath, TArray<T>& OutArray);
	FUPSkillData GetSkillDataBySKillAbilityIndex(int32 InputAction);
	int32 GetBuffTypeCount();
};

