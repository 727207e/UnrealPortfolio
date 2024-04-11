#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/UPEntityInterface.h"
#include "UPCharacter.generated.h"

UCLASS(Blueprintable)
class AUPCharacter : public ACharacter, public IUPEntityInterface
{
	GENERATED_BODY()

	public:
	AUPCharacter();
	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

public:
	virtual void SetDead();
	virtual void LookTarget(const FVector& TargetLocation) override;
	virtual FVector GetCurLocation() override;
};
