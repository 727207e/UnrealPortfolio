// Fill out your copyright notice in the Description page of Project Settings.


#include "Level/UPLevelScriptActor.h"
#include "Blueprint/UserWidget.h"
#include "UI/UPLoadLevelUserWidget.h"
#include "Components/WidgetComponent.h"
#include "Player/UPBaseController.h"
#include "Engine/LevelStreamingDynamic.h"
#include "Kismet/GameplayStatics.h"
#include "Character/UPBossCharacter.h"
#include "GAS/Attribute/EntityAttributeSet.h"

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
							LevelLoadWidget->ProgressValue = 1;
							OnLevelLoaded();
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

void AUPLevelScriptActor::OnLevelLoaded()
{
    UE_LOG(LogTemp, Log, TEXT("Level loaded successfully"));
    GetWorld()->GetTimerManager().ClearTimer(ProgressCheckTimeHandle);

    AUPBaseController* BaseController = Cast<AUPBaseController>(GetWorld()->GetFirstPlayerController());
    if (BaseController)
    {
        BaseController->AnnounceLevelLoadDone();
    }
}

void AUPLevelScriptActor::ProgressCheck()
{
	if (NextLevel.IsEmpty())
	{
		GetWorld()->GetTimerManager().ClearTimer(ProgressCheckTimeHandle);
	}

	ProgressLoad = GetAsyncLoadPercentage(FName(*NextLevel)) / 100;
	if (ProgressLoad > OldProgressLoad)
	{
		OldProgressLoad = ProgressLoad;

		LevelLoadWidget->ProgressValue = ProgressLoad;
		UE_LOG(LogTemp, Log, TEXT("Progress : %f"), ProgressLoad);
	}
}

void AUPLevelScriptActor::SetBossHp(float Value)
{
	if (HasAuthority())
	{
		TArray<AActor*> FoundActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AUPBossCharacter::StaticClass(), FoundActors);

		if (!FoundActors.IsEmpty())
		{
			AUPBossCharacter* BossCharacter = Cast<AUPBossCharacter>(FoundActors[0]);
			const_cast<UEntityAttributeSet*>(BossCharacter->GetAbilitySystemComponent()->GetSet<UEntityAttributeSet>())->SetHpValue(Value);
		}
	}
}
