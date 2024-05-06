// Fill out your copyright notice in the Description page of Project Settings.


#include "UPGameSingleton.h"

UUPGameSingleton::UUPGameSingleton(): CurrentMainCharacterId(2)
{
	static ConstructorHelpers::FObjectFinder<UDataTable> ActionDataRef(
	TEXT("/Script/Engine.DataTable'/Game/Data/ActionTableData/DT_ActionData.DT_ActionData'"));
	if (nullptr != ActionDataRef.Object)
	{
		if (ActionDataRef.Object)
		{
			ActionDataTable = ActionDataRef.Object;
		}
	}
	LoadDataTableToArray(
		TEXT("/Script/Engine.DataTable'/Game/Data/DataAttributeSet/MainCharacterDataSet/DT_MainCharacterTable.DT_MainCharacterTable'"),
		MainCharacterArray);

	LoadDataTableToArray(
		TEXT("/Script/Engine.DataTable'/Game/Data/ModelWidgetTableData/DT_SlotModelWidgetData.DT_SlotModelWidgetData'"),
		SlotWidgetModelDataArray);
	
	LoadDataTableToArray(
		TEXT("/Script/Engine.DataTable'/Game/Data/SkillData/DT_SkillDataTable.DT_SkillDataTable'"),
		SkillDataArray);
	
}
template <typename T>
void UUPGameSingleton::LoadDataTableToArray(const FString& DataTablePath, TArray<T>& OutArray)
{
    static ConstructorHelpers::FObjectFinder<UDataTable> DataTableRef(*DataTablePath);
    if (nullptr != DataTableRef.Object)
    {
        if (DataTableRef.Object)
        {
            const UDataTable* DataTable = DataTableRef.Object;
            check(DataTable->GetRowMap().Num() > 0);

            TArray<uint8*> ValueArray;
            DataTable->GetRowMap().GenerateValueArray(ValueArray);
            Algo::Transform(ValueArray, OutArray,
                            [](uint8* Value)
                            {
                                return *reinterpret_cast<T*>(Value);
                            }
            );
        }
    }
}

UUPGameSingleton& UUPGameSingleton::Get()
{
	if (UUPGameSingleton* Singleton = CastChecked< UUPGameSingleton>(GEngine->GameSingleton))
	{
		return *Singleton;
	}
	
	UE_LOG(LogTemp, Error, TEXT("Invalid Game Singleton"));
	return *NewObject<UUPGameSingleton>();
}

FUPSkillData UUPGameSingleton::GetSkillDataBySKillAbilityIndex(int32 InputAction)
{
	for(const auto& SkillData : SkillDataArray)
	{
		if(SkillData.SKillAbilityIndex == InputAction)
		{
			return  SkillData;	
		}
	}
	return {};
}
