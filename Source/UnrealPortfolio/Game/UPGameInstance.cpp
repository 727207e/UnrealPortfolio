// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/UPGameInstance.h"
#include "Kismet/GameplayStatics.h"

UUPGameInstance::UUPGameInstance()
{

}

void UUPGameInstance::LoadNextLevelByAsync(const FString& NextLevelPath)
{
	if (NextLevel.IsEmpty())
	{
		NextLevel = NextLevelPath;

		GetWorld()->GetTimerManager().SetTimer(LevelLoadStartTimeHandle, FTimerDelegate::CreateLambda([&]
			{
				LoadPackageAsync((NextLevelPath),
				FLoadPackageAsyncDelegate::CreateLambda([=, this](const FName& PackageName, UPackage* LoadedPackage, EAsyncLoadingResult::Type Result)
					{
						if (Result == EAsyncLoadingResult::Succeeded)
						{
							UE_LOG(LogTemp, Log, TEXT("Level Load Done"));
							GetWorld()->GetTimerManager().SetTimer(OpenLevelTimeHandle, this, &UUPGameInstance::OpenLevel, 1.0f, false, -1.0f);

						}
					}), 0, PKG_ContainsMap);
			}
		), 3.0f, false, -1.0f);

		GetWorld()->GetTimerManager().SetTimer(ProgressCheckTimeHandle, this, &UUPGameInstance::ProgressCheck, 0.01f, true, 2.0f);
	}

	else
	{
		UE_LOG(LogTemp, Error, TEXT("It's Already Loading Level"));
	}
}

void UUPGameInstance::OpenLevel()
{
	UGameplayStatics::OpenLevel(this, FName(*NextLevel));
	NextLevel.Empty();
}

void UUPGameInstance::ProgressCheck()
{
	if (NextLevel.IsEmpty())
	{
		GetWorld()->GetTimerManager().ClearTimer(ProgressCheckTimeHandle);
	}
	float Progress = GetAsyncLoadPercentage(FName(*NextLevel));
	if (!IsDoneCheckReady && Progress != -1.0f)
	{
		IsDoneCheckReady = true;
		UE_LOG(LogTemp, Log, TEXT("Progress Start"));
	}
	else if (IsDoneCheckReady && Progress == -1.0f)
	{
		GetWorld()->GetTimerManager().ClearTimer(ProgressCheckTimeHandle);
	}
	else if (IsDoneCheckReady)
	{
		UE_LOG(LogTemp, Log, TEXT("Progress : %f"), Progress);
	}
}