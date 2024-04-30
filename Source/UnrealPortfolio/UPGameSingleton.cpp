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

	static ConstructorHelpers::FObjectFinder<UDataTable> MainCharacterTableRef(TEXT(
		"/Script/Engine.DataTable'/Game/Data/DataAttributeSet/MainCharacterDataSet/DT_MainCharacterTable.DT_MainCharacterTable'"));
	if (nullptr != MainCharacterTableRef.Object)
	{
		if (MainCharacterTableRef.Object)
		{
			const UDataTable* DataTable = MainCharacterTableRef.Object;
			check(DataTable->GetRowMap().Num() > 0);

			TArray<uint8*> ValueArray;
			DataTable->GetRowMap().GenerateValueArray(ValueArray);
			Algo::Transform(ValueArray, MainCharacterArray,
			                [](uint8* Value)
			                {
				                return *reinterpret_cast<FUPMainCharacterClassTable*>(Value);
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
