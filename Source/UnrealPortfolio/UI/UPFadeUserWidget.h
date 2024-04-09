// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/UPUserWidget.h"
#include "Components/Image.h"
#include "Interface/CharacterMovementInterface.h"
#include "UPFadeUserWidget.generated.h"

DECLARE_DYNAMIC_DELEGATE(FOnFadeEndDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFadeEnd_MultiCastDelegate);


UCLASS()
class UNREALPORTFOLIO_API UUPFadeUserWidget : public UUPUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;

protected:
	const float ONE = 1.0f;
	const float ZERO = 0.0f;
	
protected:
	UPROPERTY(EditAnywhere , Category = Fade)
	float Duration;
	float DelTime;
	float StartData;
	float EndData;
	UPROPERTY(EditAnywhere, Category = Fade)
	TObjectPtr<class UImage> ImgFade;
	
	ICharacterMovementInterface* MovementInterface;

public:
	UFUNCTION(BlueprintCallable)
	UImage* GetImage();
	
	FOnFadeEndDelegate EndCallbackDelegate;
	
	FOnFadeEnd_MultiCastDelegate EndCallbackMultiCastDelegate;

private:
	void StartFadeIn();
	
	void StartFadeOut();
public:
	/** Only Use to Blueprint **/
	UFUNCTION()
	void StartFadeInInBlueprint(TScriptInterface<ICharacterMovementInterface>  MovementCharacter ,const FOnFadeEndDelegate& EndCallback );
public:
	UFUNCTION()
	void StartFadeOutInBlueprint(const TScriptInterface<ICharacterMovementInterface>&  MovementCharacter ,const FOnFadeEndDelegate& EndCallback );
	void StartFadeIn(ICharacterMovementInterface*  MovementCharacter ,const FOnFadeEndDelegate& EndCallback);
	void StartFadeOut(ICharacterMovementInterface*  MovementCharacter ,const FOnFadeEndDelegate& EndCallback);
	
private:
	void Fade();

private:
	FTimerHandle ActionTimer;
};
