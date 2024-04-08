// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Interface/CharacterMovementInterface.h"
#include "Interface/UPUINpcInterface.h"
#include "Interface/UPControllerInterface.h"
#include "UI/UPFadeUserWidget.h"
#include "GA_NPCInteractor.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPORTFOLIO_API UGA_NPCInteractor : public UGameplayAbility
{
	GENERATED_BODY()

private:
	const FString WidgetClassPath = "/Game/UI/WBP_Fade.WBP_Fade_C";
	
	
public:
	EMovementMode CurrentEMoveType;
	
	ICharacterMovementInterface* CharacterMovementInterface;
	IUPUINpcInterface* UPUINpcInterface;
	IUPControllerInterface* ControllerInterface;
	UPROPERTY(EditAnywhere , Category = GAS)
	TSubclassOf<class UUPFadeUserWidget> FadeUserWidgetClass;
	
 	TObjectPtr<class UUPFadeUserWidget>  FadeUserWidget;
	//TScriptInterface<class ICharacterMovementInterface>* ScriptInterface;

protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

public:
	UFUNCTION(BlueprintCallable)
	void PlayCinematicCutscene();
protected:
	UFUNCTION()
	void OnCinematicCutsceneFadeInEnd();
	UFUNCTION()
	void CinematicCutsceneFinish();
	UFUNCTION()
	void OnCompleteCallback();
	
};
