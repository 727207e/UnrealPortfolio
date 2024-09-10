// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "UPPersistentController.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPORTFOLIO_API AUPPersistentController : public APlayerController
{
	GENERATED_BODY()
	
public :
	AUPPersistentController();

	virtual void BeginPlay() override;
	
	void TryConnectToServer(const FString& Address);

public:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> PersistentHUDWidgetType;
	UPROPERTY()
	TObjectPtr<class UUserWidget> PersistentHudWidget;

private:
	void ConnectTimeOver();
	
private:
	FTimerHandle IPCheckTimerHandle;
};
