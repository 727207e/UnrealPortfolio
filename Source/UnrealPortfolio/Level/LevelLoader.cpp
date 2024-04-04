// Fill out your copyright notice in the Description page of Project Settings.


#include "Level/LevelLoader.h"
#include "UObject/UObjectGlobals.h"
#include "Kismet/GameplayStatics.h"
#include "Character/UPCharacter.h"
#include "GameFramework/PlayerStart.h"
#include "Components/BoxComponent.h"

// Sets default values
ALevelLoader::ALevelLoader()
{

}

void ALevelLoader::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(Handle, FTimerDelegate::CreateLambda([&]
		{
			UE_LOG(LogTemp, Log, TEXT("Start Timer"));
			//works
			/*FLatentActionInfo LatentInfo;
			UGameplayStatics::LoadStreamLevel(this, TEXT("TopDownSampleScene"), true, true, LatentInfo);*/
			
			LoadPackageAsync(TEXT("/Game/Level/TopDownSampleScene"),
				FLoadPackageAsyncDelegate::CreateLambda([=, this] (const FName& PackageName, UPackage* LoadedPackage, EAsyncLoadingResult::Type Result)
				{
					if (Result == EAsyncLoadingResult::Succeeded)
					{
						UE_LOG(LogTemp, Log, TEXT("Done"));
						GetWorld()->GetTimerManager().SetTimer(Handle3,this, &ALevelLoader::OpenLevel, 1.0f, false, -1.0f);
						
					}
				}),	0, PKG_ContainsMap);
		}
	), 3.0f, false, -1.0f);

	GetWorld()->GetTimerManager().SetTimer(Handle2,this, &ALevelLoader::ProgressCheck, 0.01f, true, 2.0f);
}

void ALevelLoader::LoadLevelDebug()
{
	
}

void ALevelLoader::OpenLevel()
{
	UGameplayStatics::OpenLevel(this, TEXT("TopDownSampleScene"));
}

void ALevelLoader::ProgressCheck()
{
	float Progress = GetAsyncLoadPercentage(TEXT("/Game/Level/TopDownSampleScene"));
	if (!IsDoneCheckReady && Progress != -1.0f)
	{
		IsDoneCheckReady = true;
		UE_LOG(LogTemp, Log, TEXT("Progress Start"));
	}
	else if (IsDoneCheckReady && Progress == -1.0f)
	{
		GetWorld()->GetTimerManager().ClearTimer(Handle2);
	}
	else if (IsDoneCheckReady)
	{
		UE_LOG(LogTemp, Log, TEXT("Progress : %f"), Progress);
	}
}
