#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "UPCharacter.generated.h"

UENUM()
enum class ECharacterControlType : uint8
{
	TopDown,
	Shoulder,
	SideScroll,
};

UCLASS(Blueprintable)
class AUPCharacter : public ACharacter
{
	GENERATED_BODY()

	public:
	AUPCharacter();
	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

public:
	virtual void SetDead();
};
