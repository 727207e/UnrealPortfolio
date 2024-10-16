// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"
#include "Player/UPBaseController.h"
#include "Interface/HUDControllerInterface.h"
#include "Interface/UPPossessCharacterInterface.h"
#include "UI/Componenet/WidgetHUDComponent.h"
#include "UPPlayerController.generated.h"

/** Forward declaration to improve compiling times */
class UNiagaraSystem;
class UInputMappingContext;
class UInputAction;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS()
class AUPPlayerController : public AUPBaseController,public  IHUDControllerInterface
{
	GENERATED_BODY()

	/** GAS Input Id **/
private:
	const int32 INPUT_ATTACK_START = 0;
	
public:
	AUPPlayerController();
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<class UInputMappingContext> DefaultMappingContext;
	
	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> SetDestinationClickAction;
	
	/** Skill System */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Input)
	TMap<TObjectPtr<class UInputAction>, int32> PlayerSkillRegistDictionary;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> AttackAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> AvoidAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> MenuAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> InventoryAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> InteractionAction;
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Input)
	TMap<TObjectPtr<class UInputAction>, int32> ConsumableItemDictionary;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> ChatEnterAction;
		
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> ScrollUpAction;
		
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> ScrollDownAction;
	
	UPROPERTY()
	TObjectPtr<class UUPACChatGenerator> ChatActorComponent;

	UPROPERTY()
	TObjectPtr<class UWidgetHUDComponent> HudWidgetComponent;

	FORCEINLINE TObjectPtr<class UUPMainHudWidget> GetHudWidget() { return HudWidgetComponent->MainHudWidget; }

protected:
	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;

	virtual void SetupInputComponent() override;
	// To add mapping context
	virtual void BeginPlay();

	/** Input handlers for SetDestination action. */
	void OnInputStarted();
	void OnSetDestinationTriggered();
	void OnSetDestinationReleased();

private:
	void OnSkillStart(int32 InputId);
	void OnSkillRelease(int32 InputId);

	void OnAttackStart();
	void OnConsumableItemStart(int32 InputID);

	void OnAvoidStart();

	void OnMenuStart();
	void OnInventoryStart();
	void OnNPCInteraction();

	void ChatFocusOn();
	void ChatScroll(bool bUp);


	IUPPossessCharacterInterface* PossessCharacter;
	
	/** Game Ability System Input Component **/
protected:
	void GASInputPressed(int32 InputId);
	

//Character Skill Manage
private:
	TArray<bool> SkillCoolDownData;

public:
	void SkillSetting();
	bool IsSkillCoolDown(int32 SkillNumber);
	void SkillSettingCoolDown(int32 SkillNumber, int32 SkillCoolDown);
	void BuffIconActive();

	UFUNCTION(Client, Unreliable)
	void Client_BuffIconActive();
};