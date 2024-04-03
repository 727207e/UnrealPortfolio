// Fill out your copyright notice in the Description page of Project Settings.


#include "Gimmick/UPNPCDetectorSceneComponent.h"

#include "Character/UPMainCharacter.h"
#include "Character/UPNPCCharacter.h"
#include "Components/BoxComponent.h"
#include "Interface/UPUINpcInterface.h"
#include "defines/UPCollision.h"
// Sets default values for this component's properties
UUPNPCDetectorSceneComponent::UUPNPCDetectorSceneComponent()
{
	SizeX = 100.0f;
	SizeY = 100.0f;
	SizeZ = 100.0f;
	
	BoxComp = CreateDefaultSubobject<UBoxComponent>("BoxComponent");
	BoxComp->SetBoxExtent(FVector(SizeX,SizeY,SizeZ));
	BoxComp->SetCollisionProfileName(CPROFILE_NPC);
	BoxComp->OnComponentBeginOverlap.AddDynamic(this,&UUPNPCDetectorSceneComponent::OnOverlapBegin);
	BoxComp->OnComponentEndOverlap.AddDynamic(this,&UUPNPCDetectorSceneComponent::OnOverlapEnd);
}

void UUPNPCDetectorSceneComponent::Action() const
{
	if(UINPC != nullptr)
	{
		UINPC->TakeNPCWidget();
	}
}

void UUPNPCDetectorSceneComponent::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult)
{
	const auto Character = Cast<IUPUINpcInterface>(OtherActor);
	if(Character == nullptr)
	{
		return;
	}
	UINPC = Character;
	UINPC->ShowInterAction();
}

void UUPNPCDetectorSceneComponent::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp,Log,TEXT("NPC Is Null"));
	const IUPUINpcInterface* ExistActor = Cast<IUPUINpcInterface>(OtherActor);

	if(ExistActor == UINPC)
	{
		UINPC->HideInterAction();
		UINPC = nullptr;
	}
}

void UUPNPCDetectorSceneComponent::SetParent(USceneComponent* InParent)
{
	this->SetupAttachment(InParent);
	BoxComp->SetupAttachment(InParent);	
}
