#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/UPEntityInterface.h"
#include "UPCharacter.generated.h"

UCLASS(Abstract)
class AUPCharacter : public ACharacter, public IUPEntityInterface
{
	GENERATED_BODY()

public:
	AUPCharacter();

public:
	UFUNCTION()
	virtual void OnDead() PURE_VIRTUAL(ACharacter::OnDead(), );

	virtual void LookTarget(const FVector& TargetLocation) override;
	virtual FVector GetCurLocation() override;
};
