// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/GA/GA_NPCInteractor.h"

#include "EngineUtils.h"
#include "Character/UPMainCharacter.h"
#include "Interface/UPControllerInterface.h"
#include "UI/UPFadeUserWidget.h"

class FOnFadeEndDelegate;
void UGA_NPCInteractor::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                        const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                        const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	auto MainCharacter = CastChecked<AUPMainCharacter>(ActorInfo->AvatarActor);
	ControllerInterface = CastChecked<IUPControllerInterface>(MainCharacter->GetController()); 
	CharacterMovementInterface = MainCharacter;
	UPUINpcInterface = MainCharacter->GetNPCInterface();
	if(UPUINpcInterface == nullptr)
	{
		OnCompleteCallback();
		return;
	}
	PlayCinematicCutscene();
	
}

void UGA_NPCInteractor::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UGA_NPCInteractor::PlayCinematicCutscene()
{
	
	if (FadeUserWidget == nullptr)
	{
		UClass* WidgetClass = LoadClass<UUserWidget>(nullptr, *WidgetClassPath);
		FadeUserWidget = CastChecked<UUPFadeUserWidget>(CreateWidget(GetWorld(),WidgetClass,TEXT("WBP_FadeWidget")));
		FadeUserWidget->AddToViewport();
	}
	
	FOnFadeEndDelegate OnFadeEndDelegate;
	OnFadeEndDelegate.BindDynamic(this,&UGA_NPCInteractor::OnCinematicCutsceneFadeInEnd);
	ECharacterControlType Type =  CharacterMovementInterface->GetCharacterControl();
	if(Type == ECharacterControlType::TopDown)
	{
		UPUINpcInterface->HideInterActionAlarm();
	}
	else if(Type == ECharacterControlType::Shoulder)
	{
		UPUINpcInterface->TakeNPCWidgetHide();
	}
	FadeUserWidget->StartFadeIn(CharacterMovementInterface,OnFadeEndDelegate);
	
}


void UGA_NPCInteractor::OnCinematicCutsceneFadeInEnd()
{
	FOnFadeEndDelegate OnFadeEndDelegate;
	ECharacterControlType Type =  CharacterMovementInterface->GetCharacterControl();
	if(Type == ECharacterControlType::TopDown)
	{
		CharacterMovementInterface->SetCharacterControl(ECharacterControlType::Shoulder);
	}
	else if(Type == ECharacterControlType::Shoulder)
	{
		CharacterMovementInterface->SetCharacterControl(ECharacterControlType::TopDown);
	}
	
	
	OnFadeEndDelegate.BindDynamic(this,&UGA_NPCInteractor::CinematicCutsceneFinish);
	FadeUserWidget->StartFadeOut(CharacterMovementInterface,OnFadeEndDelegate);
}

void UGA_NPCInteractor::CinematicCutsceneFinish()
{
	ECharacterControlType Type =  CharacterMovementInterface->GetCharacterControl();
	if(Type == ECharacterControlType::TopDown)
	{
		UPUINpcInterface->ShowInteractionAlarm();
		CharacterMovementInterface->SetCharacterMovementMod(MOVE_Walking);
	}
	else if(Type == ECharacterControlType::Shoulder)
	{
		UPUINpcInterface->TakeNPCWidgetShow();
		ControllerInterface->SetIgnoreLookInputInterface(true);
		CharacterMovementInterface->SetCharacterMovementMod(MOVE_None);
	}
	
	OnCompleteCallback();
}

void UGA_NPCInteractor::OnCompleteCallback()
{
	
	//리플리케이션에대한 사용여부 (네트워크)
	bool bReplicatedEndAbility = true;
	//취소 여부
	bool bWasCancelled = false;
	
	EndAbility(CurrentSpecHandle,CurrentActorInfo,CurrentActivationInfo,bReplicatedEndAbility,bWasCancelled);
}
