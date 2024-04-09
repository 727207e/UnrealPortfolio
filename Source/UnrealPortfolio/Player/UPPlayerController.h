// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"
#include "GameFramework/PlayerController.h"
#include "Interface/UPControllerInterface.h"
#include "Interface/UPPossessCharacterInterface.h"
#include "UPPlayerController.generated.h"

/** Forward declaration to improve compiling times */
class UNiagaraSystem;
class UInputMappingContext;
class UInputAction;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS()
class AUPPlayerController : public APlayerController, public IUPControllerInterface
{
	GENERATED_BODY()

public:
	AUPPlayerController();

	virtual void SetPossessCharacterInterface(class IUPPossessCharacterInterface* TargetCharacter) override;


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
	
protected:
	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;

	virtual void SetupInputComponent() override;
	virtual void SetIgnoreLookInputInterface(bool bcheck) override;
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

	IUPPossessCharacterInterface* PossessCharacter;
	
	/** Game Ability System Input Component **/
protected:
	void GASInputPressed(int32 InputId);
};