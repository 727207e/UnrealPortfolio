// Fill out your copyright notice in the Description page of Project Settings.


#include "Level/UPLevelScriptActor.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "UI/UPLoadLevelUserWidget.h"
#include "Components/WidgetComponent.h"

AUPLevelScriptActor::AUPLevelScriptActor()
{
	static ConstructorHelpers::FClassFinder<UUPLoadLevelUserWidget> LevelLoadWidgetBlueprint(TEXT("/Game/Blueprint/UI/WBP_LevelLoading.WBP_LevelLoading_C"));

	if (LevelLoadWidgetBlueprint.Class)
	{
		LevelLoadWidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("LevelLoadWidgetComponent"));
		LevelLoadWidgetComp->SetupAttachment(RootComponent);
		LevelLoadWidgetComp->SetWidgetClass(LevelLoadWidgetBlueprint.Class);
		LevelLoadWidgetComp->SetWidgetSpace(EWidgetSpace::World);
		LevelLoadWidgetComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

void AUPLevelScriptActor::LoadNextLevelByAsync(const FString& NextLevelPath)
{
	if (NextLevel.IsEmpty())
	{
		if (LevelLoadWidget == nullptr)
		{
			LevelLoadWidget = Cast<UUPLoadLevelUserWidget>(LevelLoadWidgetComp->GetWidget());
		}
		LevelLoadWidget->AddToViewport();
		NextLevel = NextLevelPath;

		GetWorld()->GetTimerManager().SetTimer(LevelLoadStartTimeHandle, FTimerDelegate::CreateLambda([&]
			{
				LoadPackageAsync((NextLevelPath),
				FLoadPackageAsyncDelegate::CreateLambda([=, this](const FName& PackageName, UPackage* LoadedPackage, EAsyncLoadingResult::Type Result)
					{
						if (Result == EAsyncLoadingResult::Succeeded)
						{
							UE_LOG(LogTemp, Log, TEXT("Level Load Done"));
							GetWorld()->GetTimerManager().SetTimer(OpenLevelTimeHandle, this, &AUPLevelScriptActor::OpenLevel, 1.0f, false, -1.0f);
						}
					}), 0, PKG_ContainsMap);
			}
		), 1.0f, false, -1.0f);

		UE_LOG(LogTemp, Log, TEXT("Level UI Active"));
		GetWorld()->GetTimerManager().SetTimer(ProgressCheckTimeHandle, this, &AUPLevelScriptActor::ProgressCheck, 0.01f, true, 0.0f);
	}

	else
	{
		UE_LOG(LogTemp, Error, TEXT("It's Already Loading Level"));
	}
}

void AUPLevelScriptActor::OpenLevel()
{
	UGameplayStatics::OpenLevel(this, FName(*NextLevel));
	NextLevel.Empty();
}

void AUPLevelScriptActor::ProgressCheck()
{
	if (NextLevel.IsEmpty())
	{
		GetWorld()->GetTimerManager().ClearTimer(ProgressCheckTimeHandle);
	}

	ProgressLoad = GetAsyncLoadPercentage(FName(*NextLevel));
	if (!IsDoneCheckReady && ProgressLoad != -1.0f)
	{
		IsDoneCheckReady = true;
		UE_LOG(LogTemp, Log, TEXT("Progress Start"));
	}
	else if (IsDoneCheckReady && ProgressLoad == -1.0f)
	{

		UE_LOG(LogTemp, Log, TEXT("Level UI Deactive"));
		LevelLoadWidget->ProgressValue = 100;
		GetWorld()->GetTimerManager().ClearTimer(ProgressCheckTimeHandle);
	}
	else if (IsDoneCheckReady)
	{
		LevelLoadWidget->ProgressValue = ProgressLoad;
		UE_LOG(LogTemp, Log, TEXT("Progress : %f"), ProgressLoad);
	}

}