// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/UPCharacter.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "Interface/AbilitySystemGetInterface.h"
#include "Interface/CharacterMovementInterface.h"
#include "Interface/UPPossessCharacterInterface.h"
#include "Interface/UPUINpcInterface.h"
#include "UPMainCharacter.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPORTFOLIO_API AUPMainCharacter : public AUPCharacter, public IAbilitySystemGetInterface, public IUPPossessCharacterInterface ,public ICharacterMovementInterface
{
	GENERATED_BODY()
	
public :
	AUPMainCharacter();
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	virtual void PossessedBy(AController* NewController) override;

	virtual	void OnAttackStart() override;
	virtual void OnSkillStart(int32 Index) override;
	virtual void OnSkillRelease(int32 Index) override;
	virtual void OnConsumableStart(int32 Index) override;
	virtual void OnAvoidStart() override;
	virtual void OnMenuStart() override;
	virtual void OnInventoryStart() override;
	virtual void OnInputStart() override;
	virtual void OnSetDestinationTriggered() override;
	virtual void OnSetDestinationReleased() override;
	virtual void OnNPCInteraction() override;
	virtual void BeginPlay() override;
	
	/** Time Threshold to know if it was a short press */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	float ShortPressThreshold;

	/** FX Class that we will spawn when clicking */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<class UNiagaraSystem> FXCursor;

protected :
	UPROPERTY(EditAnywhere, Category = GAS)
	TObjectPtr<class UAbilitySystemComponent> ASC;

	UPROPERTY(EditAnywhere, Category = GAS)
	TArray<TSubclassOf<class UGameplayAbility>> StartAbilities;
	
	UPROPERTY(EditAnywhere, Category = GAS)
	TMap<int32, TSubclassOf<class UGameplayAbility>> StartInputAbilities;

	UPROPERTY(EditAnywhere, Category = NPC)
	TObjectPtr<class UUPNPCDetectorSceneComponent> NPCDetectorSceneComponent;
private :
	void SetupGasInput(AController* NewController);
public:
	IUPUINpcInterface* GetNPCInterface();

protected:
	//Movement
	float FollowTime; // For how long it has been pressed
	FVector CachedDestination;


protected:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* CameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;
	
protected:
	/** Camera Control Data */
	UPROPERTY(EditAnywhere, Category = CharacterControl, Meta = (AllowPrivateAccess = "true"))
	TMap<ECharacterControlType, class UUPCharacterControlData*> CharacterControlManager;
	/** CurrentCharacterControlType */
	ECharacterControlType CurrentCharacterControlType;
protected:
	void SetupPlayerCamera();
	/**Set Current Player Camera Data **/
	void SetCharacterControlData(const UUPCharacterControlData* CharacterControlData);
public:
	/**Set Current Player Control Data **/
	UFUNCTION(BlueprintCallable)
	virtual  void SetCharacterControl(ECharacterControlType NewCharacterControlType) override;

/** Game Ability System**/
protected:
	void GASInputPressed(int32 GameplayAbilityInputId);

protected:
	virtual void SetCharacterMovementMod(EMovementMode MovementMode) override;
	virtual ECharacterControlType GetCharacterControl() override;
	
	
};
