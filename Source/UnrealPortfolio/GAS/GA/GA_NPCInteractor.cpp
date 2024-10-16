// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/GA/GA_NPCInteractor.h"

#include "EngineUtils.h"
#include "Character/UPMainCharacter.h"
#include "Interface/UPControllerInterface.h"
#include "UI/UPFadeUserWidget.h"
#include "Tag/GameplayTags.h"
class FOnFadeEndDelegate;

UGA_NPCInteractor::UGA_NPCInteractor()
{
	AbilityTags.AddTag(TAG_ACTOR_INTERACTION);
	ActivationOwnedTags.AddTag(TAG_PLAYER_INTERACTING_WITH_NPC);
}

void UGA_NPCInteractor::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                        const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                        const FGameplayEventData* TriggerEventData)
{
	if (!IsLocallyControlled())
	{
		return;
	}

	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	auto MainCharacter = CastChecked<AUPMainCharacter>(ActorInfo->AvatarActor);
	CharacterMovementInterface = MainCharacter;
	CharacterEntityInterface = CastChecked<IUPEntityInterface>(MainCharacter);
	UPUINpcInterface = MainCharacter->GetNPCInterface();
	NPCEntityInterface = MainCharacter->GetNPCEntityInterface();
	
	bOnCancelAbility = false;
	if(UPUINpcInterface == nullptr || NPCEntityInterface == nullptr)
	{
		Super::CancelAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true);
		return;
	}
	PlayCinematicCutscene();
}

void UGA_NPCInteractor::CancelAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateCancelAbility)
{
	bOnCancelAbility = true;
	if(UPUINpcInterface == nullptr || !FadeUserWidget || NPCEntityInterface == nullptr)
	{
		Super::CancelAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true);
		return;
	}
	PlayCancelCinematicCutscene();
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
	UPUINpcInterface->HideInterActionAlarm();
	FadeUserWidget->StartFadeIn(CharacterMovementInterface,OnFadeEndDelegate);
}

void UGA_NPCInteractor::PlayCancelCinematicCutscene()
{
	FOnFadeEndDelegate OnFadeEndDelegate;
	OnFadeEndDelegate.BindDynamic(this,&UGA_NPCInteractor::OnCinematicCutsceneFadeInEnd);
	UPUINpcInterface->TakeNPCWidgetHide();
	FadeUserWidget->StartFadeIn(CharacterMovementInterface,OnFadeEndDelegate);
}


void UGA_NPCInteractor::OnCinematicCutsceneFadeInEnd()
{
	FOnFadeEndDelegate OnFadeEndDelegate;
	if(!bOnCancelAbility)
	{
		FVector CharacterLoction = CharacterEntityInterface->GetCurLocation();
		FVector NPCLocation = NPCEntityInterface->GetCurLocation();

		//Look Each other
		NPCEntityInterface->LookTarget(CharacterLoction);
		CharacterEntityInterface->LookTarget(NPCLocation);

		//Camera Location Setting
		FTransform CameraTransform = UPUINpcInterface->GetNPCCameraTransform();
		FVector CenterTwoVector = (CharacterLoction + NPCLocation) / 2.0f;
		FVector Direction = CameraTransform.GetUnitAxis(EAxis::X);

		CenterTwoVector -= (Direction * 1000);
		CameraTransform.SetLocation(CenterTwoVector);

		CharacterMovementInterface->SetCharacterControl(ECharacterControlType::NPC, CameraTransform);
	}
	else
	{
		CharacterMovementInterface->SetCharacterControl(ECharacterControlType::TopDown);
	}
	OnFadeEndDelegate.BindDynamic(this,&UGA_NPCInteractor::CinematicCutsceneFinish);
	FadeUserWidget->StartFadeOut(CharacterMovementInterface,OnFadeEndDelegate);
}

void UGA_NPCInteractor::CinematicCutsceneFinish()
{
	if(bOnCancelAbility)
	{
		UPUINpcInterface->ShowInteractionAlarm();
		CharacterMovementInterface->SetCharacterMovementMod(MOVE_Walking);
		Super::CancelAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true);
	}
	else
	{
		UPUINpcInterface->TakeNPCWidgetShow();
		CharacterMovementInterface->SetCharacterMovementMod(MOVE_None);
	}
}