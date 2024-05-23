// Fill out your copyright notice in the Description page of Project Settings.


#include "Level/UPLevelScriptActor.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "UI/UPLoadLevelUserWidget.h"
#include "Components/WidgetComponent.h"
#include "Engine/LevelStreamingDynamic.h"

AUPLevelScriptActor::AUPLevelScriptActor()
{
	static ConstructorHelpers::FClassFinder<UUPLoadLevelUserWidget> LevelLoadWidgetBlueprint(TEXT("/Game/UI/WBP_LevelLoading.WBP_LevelLoading_C"));

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
    if (LevelLoadWidget == nullptr)
    {
        LevelLoadWidget = Cast<UUPLoadLevelUserWidget>(LevelLoadWidgetComp->GetWidget());
    }
    if (LevelLoadWidget != nullptr)
    {
        LevelLoadWidget->AddToViewport();

        if (!NextLevelPath.IsEmpty())
        {
            UE_LOG(LogTemp, Log, TEXT("Starting async load for level: %s"), *NextLevelPath);

            LevelName = NextLevelPath;
            UWorld* World = GetWorld();
            if (World)
            {
                bool StreamingLevelResult = true;
                ULevelStreamingDynamic* StreamingLevel = ULevelStreamingDynamic::LoadLevelInstance(GetWorld(), NextLevelPath, FVector::ZeroVector, FRotator::ZeroRotator, StreamingLevelResult);
                if (StreamingLevel)
                {
                    StreamingLevel->OnLevelLoaded.AddDynamic(this, &AUPLevelScriptActor::OnLevelLoaded);
                    GetWorld()->GetTimerManager().SetTimer(ProgressCheckTimeHandle, FTimerDelegate::CreateLambda([this, StreamingLevel]()
                        {
                            if (StreamingLevel)
                            {
                                float LoadProgress = StreamingLevel->GetLevelStreamingStatus() == LEVEL_Visible ? 1.0f : StreamingLevel->GetLevelStreamingStatus() / 100.0f;
                                LevelLoadWidget->ProgressValue = LoadProgress;
                                UE_LOG(LogTemp, Log, TEXT("Level load progress: %f"), LoadProgress);
                            }
                        }), 0.1f, true);
                }
                else
                {
                    UE_LOG(LogTemp, Error, TEXT("Failed to create streaming level: %s"), *NextLevelPath);
                }
            }
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("NextLevelPath is empty!"));
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("LevelLoadWidget is null and could not be added to the viewport."));
    }
}

void AUPLevelScriptActor::OnLevelLoaded()
{
    UE_LOG(LogTemp, Log, TEXT("Level loaded successfully"));
    GetWorld()->GetTimerManager().ClearTimer(ProgressCheckTimeHandle);

    LevelLoadWidget->ProgressValue = 1;
    UGameplayStatics::OpenLevel(this, FName(*LevelName));
}