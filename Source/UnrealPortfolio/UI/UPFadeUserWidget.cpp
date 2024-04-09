// Fill out your copyright notice in the Description page of Project Settings.
#include "UI/UPFadeUserWidget.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Interface/CharacterMovementInterface.h"

void UUPFadeUserWidget::NativeConstruct()
{
	Super::NativeConstruct();
	Duration = 1.0f;
	ImgFade =  Cast<UImage>(GetWidgetFromName(TEXT("ImageFade")));
	if(ImgFade)
	{
		ImgFade->SetColorAndOpacity(FLinearColor:: Black);
		ImgFade->SetOpacity(0.0f);
	}
}

UImage* UUPFadeUserWidget::GetImage()
{
	return  ImgFade;
}

void UUPFadeUserWidget::StartFadeIn()
{
	if (ActionTimer.IsValid()) { return; }

	if (MovementInterface == nullptr) { return; }
	
	DelTime = ZERO;
	StartData = ZERO;
	EndData = 1.0f - StartData;
	
	MovementInterface->SetCharacterMovementMod(MOVE_None);
	
	ImgFade->SetOpacity(StartData);
	ImgFade->SetColorAndOpacity(FLinearColor:: Black);
	ImgFade->SetOpacity(0.0f);
	
	GetWorld()->GetTimerManager().ClearTimer(ActionTimer);
	GetWorld()->GetTimerManager().SetTimer(ActionTimer,this,&UUPFadeUserWidget::Fade,0.01f,true,Duration);
}


void UUPFadeUserWidget::StartFadeInInBlueprint(TScriptInterface<ICharacterMovementInterface> MovementCharacter,const FOnFadeEndDelegate& EndCallback)
{
	ICharacterMovementInterface* MovementInterfacePtr = MovementCharacter.GetInterface();
	if(MovementInterfacePtr != nullptr)
	{
		MovementInterface = MovementInterfacePtr;
		EndCallbackDelegate = EndCallback;
		StartFadeIn();
	}
}
// 멀티케스트 델리게이트 테스트용으로 사용
// void UUPFadeUserWidget::StartFadeInMultiCast(ICharacterMovementInterface* MovementCharacter,
// 									const FOnFadeEnd_MultiCastDelegate& EndCallback)
// {
// 	MovementInterface = MovementCharacter;
// 	EndCallbackMultiCastDelegate = EndCallback;
// 	StartFadeIn();
// }

void UUPFadeUserWidget::StartFadeOut()
{
	if (ActionTimer.IsValid() || !MovementInterface) { return; }
	
	MovementInterface->SetCharacterMovementMod(MOVE_None);
	DelTime = ZERO;
	StartData = ONE;
	EndData = 1.0f - StartData;
	ImgFade->SetColorAndOpacity(FLinearColor:: Black);
	ImgFade->SetOpacity(StartData);
	
	GetWorld()->GetTimerManager().ClearTimer(ActionTimer);
	GetWorld()->GetTimerManager().SetTimer(ActionTimer,this,&UUPFadeUserWidget::Fade,0.01f,true,Duration);
}


void UUPFadeUserWidget::StartFadeOutInBlueprint(const TScriptInterface<ICharacterMovementInterface>& MovementCharacter,
	const FOnFadeEndDelegate& EndCallback)
{
	ICharacterMovementInterface* MovementInterfacePtr = MovementCharacter.GetInterface();
	if(MovementInterfacePtr != nullptr)
	{
		MovementInterface = MovementInterfacePtr;
		EndCallbackDelegate = EndCallback;
		StartFadeOut();
	}

}

void UUPFadeUserWidget::StartFadeIn(ICharacterMovementInterface* MovementCharacter, const FOnFadeEndDelegate& EndCallback)
{
	if(MovementCharacter != nullptr)
	{
		MovementInterface = MovementCharacter;
		EndCallbackDelegate = EndCallback;
		StartFadeIn();
	}
}

void UUPFadeUserWidget::StartFadeOut(ICharacterMovementInterface* MovementCharacter,
	const FOnFadeEndDelegate& EndCallback)
{
	if(MovementCharacter != nullptr)
	{
		MovementInterface = MovementCharacter;
		EndCallbackDelegate = EndCallback;
		StartFadeOut();
	}
}


void UUPFadeUserWidget::Fade()
{
	if(!ActionTimer.IsValid())
	{
		return;
	}
	DelTime += UKismetSystemLibrary::K2_GetTimerElapsedTimeHandle(GetWorld(),ActionTimer);
	const float Alpha = DelTime / Duration;
	const float Opacity = FMath::Lerp(StartData,EndData,Alpha);
	ImgFade->SetOpacity(Opacity);

	if(DelTime >= Duration)
	{
		GetWorld()->GetTimerManager().ClearTimer(ActionTimer);
		ImgFade->SetOpacity(EndData);
		MovementInterface->SetCharacterMovementMod(MOVE_Walking);
		if(EndCallbackDelegate.IsBound())
		{
			EndCallbackDelegate.ExecuteIfBound();	
		}
		else
		{
			EndCallbackMultiCastDelegate.Broadcast();
		}
	}
	
}
