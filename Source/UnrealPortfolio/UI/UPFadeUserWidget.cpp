// Fill out your copyright notice in the Description page of Project Settings.
#include "UI/UPFadeUserWidget.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Interface/CharacterMovementInterface.h"

void UUPFadeUserWidget::NativeConstruct()
{
	Super::NativeConstruct();
	Duration = 1.0f;
	Img =  Cast<UImage>(GetWidgetFromName(TEXT("ImageFade")));
	if(Img)
	{
		Img->SetColorAndOpacity(FLinearColor:: Black);
		Img->SetOpacity(0.0f);
		Type = EFadeType::FadeIn;
	}
}

UImage* UUPFadeUserWidget::GetImage()
{
	return  Img;
}



void UUPFadeUserWidget::StartFade(TScriptInterface<ICharacterMovementInterface> MovementCharacter)
{
	if(ActionTimer.IsValid())	{	return;	}
	//이동 제한
	if(MovementCharacter)
	{
		MovementInterface = MovementCharacter;
		MovementInterface->SetCharacterMovementMod(MOVE_None);
	}
	
	switch (Type)
	{
		case EFadeType::FadeIn:StartFadeIn();	break;
		case EFadeType::FadeOut:StartFadeOut();	break;
	}
}

void UUPFadeUserWidget::StartFadeIn()
{
	DelTime = 0.0f;
	GetWorld()->GetTimerManager().ClearTimer(ActionTimer);
	Img->SetColorAndOpacity(FLinearColor:: Black);
	Img->SetOpacity(0.0f);
	GetWorld()->GetTimerManager().SetTimer(ActionTimer,this,&UUPFadeUserWidget::FadeIn,0.01f,true,Duration);

}

void UUPFadeUserWidget::StartFadeOut()
{
	DelTime = 0.0f;
	GetWorld()->GetTimerManager().ClearTimer(ActionTimer);
	Img->SetColorAndOpacity(FLinearColor:: Black);
	Img->SetOpacity(1.0f);
	GetWorld()->GetTimerManager().SetTimer(ActionTimer,this,&UUPFadeUserWidget::FadeOut,0.01f,true,Duration);
}

void UUPFadeUserWidget::FadeIn()
{
	if(!ActionTimer.IsValid())
	{
		UE_LOG(LogTemp,Log,TEXT("Not Found ActionTimer"));
		return;
	}
	
	const float StartData = 0.0f;
	const float EndData = 1.0f;
	DelTime += UKismetSystemLibrary::K2_GetTimerElapsedTimeHandle(GetWorld(),ActionTimer);
	const float Alpha = DelTime / Duration;
	const float Opacity = FMath::Lerp(StartData,EndData,Alpha);
	Img->SetOpacity(Opacity);

	if(DelTime >= Duration)
	{
	
		GetWorld()->GetTimerManager().ClearTimer(ActionTimer);
		Img->SetOpacity(EndData);
		Type = EFadeType::FadeOut;
		MovementInterface->SetCharacterMovementMod(MOVE_Walking);
	}
	
}

void UUPFadeUserWidget::FadeOut()
{
	if(!ActionTimer.IsValid())
	{
		return;
	}
	const float StartData = 1.0f;
	const float EndData = 0.0f;
	
	DelTime += UKismetSystemLibrary::K2_GetTimerElapsedTimeHandle(GetWorld(),ActionTimer);
	const float Alpha = DelTime / Duration;
	const float Opacity = FMath::Lerp(StartData,EndData,Alpha);
	Img->SetOpacity(Opacity);

	if(DelTime >= Duration)
	{
		UE_LOG(LogTemp,Log,TEXT("Switch FadeIn"));
		GetWorld()->GetTimerManager().ClearTimer(ActionTimer);
		Img->SetOpacity(EndData);
		Type = EFadeType::FadeIn;
		if(MovementInterface)
		{
			MovementInterface->SetCharacterMovementMod(MOVE_Walking);	
		}
		
	}
}
