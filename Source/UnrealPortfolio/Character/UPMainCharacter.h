// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "UPBattleBaseCharacter.h"
#include "Character/UPCharacter.h"
#include "Interface/CharacterMovementInterface.h"
#include "Interface/HUDControllerInterface.h"
#include "Interface/UPPossessCharacterInterface.h"
#include "Interface/UPUINpcInterface.h"
#include "UPMainCharacter.generated.h"

UCLASS()
class UNREALPORTFOLIO_API AUPMainCharacter : public AUPBattleBaseCharacter
	,public IUPPossessCharacterInterface
	,public ICharacterMovementInterface
{
	GENERATED_BODY()
private:
	const int32 GAS_START_ABILITY_ID_GAME_RESULT = 3;
	
	const int32 GAS_INPUT_ID_ATTACK_START = 0;
	const int32 GAS_INPUT_ID_AVOID_START = 10;
	
public :
	AUPMainCharacter();
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
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
	
public:
	/* Animation */
	virtual void SetDead() override;
	void PlayDeadAnimation();
	
	/** Time Threshold to know if it was a short press */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	float ShortPressThreshold;

	/** FX Class that we will spawn when clicking */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<class UNiagaraSystem> FXCursor;

protected :
	UPROPERTY(EditAnywhere, Category = NPC)
	TObjectPtr<class UUPNPCDetectorSceneComponent> NPCDetectorSceneComponent;
private :
	void SetupGasInput(AController* NewController);
public:
	IUPUINpcInterface* GetNPCInterface();
	IUPEntityInterface* GetNPCEntityInterface();

protected:
	/** Movement **/ 
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
	void SetCameraComponent(ECharacterControlType CharacterControlType, FTransform CameraTransform);
public:
	/**Set Current Player Control Data **/
	UFUNCTION(BlueprintCallable)
	virtual  void SetCharacterControl(ECharacterControlType NewCharacterControlType, FTransform TargetTransform = FTransform()) override;
	
public :
	UFUNCTION(BlueprintCallable)
	FORCEINLINE class UCameraComponent* GetCameraComponent() { return CameraComponent; }
	UFUNCTION(BlueprintCallable)
	FORCEINLINE class USpringArmComponent* GetCameraBoom() { return CameraBoom; }

public:
	/** Movement Character Interface **/
	virtual ECharacterControlType GetCharacterControl() override;

	virtual void SetCharacterMovementMod(EMovementMode MovementMode) override;

	UFUNCTION(Server, Reliable)
	void ServerSetControllerMovementMod(EMovementMode MovementMode, APlayerController* PlayerController);

private :
	void SetControllerMovementMod(EMovementMode MovementMode, APlayerController* PlayerController);

protected:
	/** Setup MainCharacter Table Data **/
	void SetMainCharacterTableData() const;

	virtual void SetupASCClientPlayer() override;
	virtual void SetupASCHostPlayer(AActor* InOwnerActor) override;
	virtual void OnDead() override;

	UFUNCTION(BlueprintCallable , Category = GAS)
	void ActiveAbilityGameOverCheck();

private:
	/** Hud PlayerState **/
	void SendPlayerStateToClient();
	UFUNCTION(Server, Reliable)
	void ServerRequestPlayerState();
	UFUNCTION(Client, Reliable)
	void ClientReceivePlayerState(AUPPlayerController* ClientController, APlayerState* ClientPlayerState);
	virtual AUPPlayerState* GetUPPlayerState() override;
};