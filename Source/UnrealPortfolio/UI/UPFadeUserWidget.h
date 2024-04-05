// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/UPUserWidget.h"
#include "Components/Image.h"
#include "Interface/CharacterMovementInterface.h"
#include "UPFadeUserWidget.generated.h"

DECLARE_DELEGATE(FOnFadeEndDelegate);

UENUM()
enum class EFadeType : int8
{
	FadeIn = 0,
	FadeOut = 1,
};

USTRUCT(BlueprintType)
struct FDelegateWrapper
{
	GENERATED_BODY()
	FDelegateWrapper(){}
	FDelegateWrapper(const FOnFadeEndDelegate& Delegate) : OnEndCallback(Delegate) {}

	FOnFadeEndDelegate OnEndCallback;
};




UCLASS()
class UNREALPORTFOLIO_API UUPFadeUserWidget : public UUPUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;

	
	UPROPERTY(EditAnywhere , Category = Fade)
	EFadeType Type;
	// 지속시간
	UPROPERTY(EditAnywhere , Category = Fade)
	float Duration;

	UPROPERTY()
	float DelTime;
	
	
	// 시작값

	// 종료값

	// 보간값

	// 지속된 시간 / 지속시간
	UPROPERTY(EditAnywhere, Category = Fade)
	TObjectPtr<class UImage> Img;

	TScriptInterface<ICharacterMovementInterface> MovementInterface;

public:
	UFUNCTION(BlueprintCallable)
	UImage* GetImage();

	
	FOnFadeEndDelegate* EndCallbackDelegate;

public:
	
	void StartFade(TScriptInterface<ICharacterMovementInterface> MovementCharacter);
	
private:
	UFUNCTION(BlueprintCallable)
	void StartFadeIn();
	UFUNCTION(BlueprintCallable)
	void StartFadeOut();
	UFUNCTION(BlueprintCallable)
	void FadeIn();

private:
	void FadeOut();
	FTimerHandle ActionTimer;
};
