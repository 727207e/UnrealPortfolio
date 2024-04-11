// Fill out your copyright notice in the Description page of Project Settings.


#include "Gimmick/UPNPCDetectorSceneComponent.h"

#include "Character/UPMainCharacter.h"
#include "Character/UPNPCCharacter.h"
#include "Components/BoxComponent.h"
#include "Interface/UPEntityInterface.h"
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

void UUPNPCDetectorSceneComponent::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult)
{
	const auto Character = Cast<IUPUINpcInterface>(OtherActor);
	const auto NPCEntity = Cast<IUPEntityInterface>(OtherActor);
	if(Character == nullptr || NPCEntity == nullptr)
	{
		return;
	}
	UINPC = Character;
	UINPC->ShowInteractionAlarm();

	NPCEntityInterface = NPCEntity;
}

void UUPNPCDetectorSceneComponent::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	
	const IUPUINpcInterface* ExistActor = Cast<IUPUINpcInterface>(OtherActor);

	if (UINPC == nullptr)
	{
		return;
	}

	if(ExistActor == UINPC)
	{
		UINPC->HideInterActionAlarm();
		UINPC = nullptr;
	}
}

void UUPNPCDetectorSceneComponent::SetParent(USceneComponent* InParent)
{
	this->AttachToComponent(InParent, FAttachmentTransformRules::KeepRelativeTransform);
	BoxComp->AttachToComponent(InParent, FAttachmentTransformRules::KeepRelativeTransform);
	BoxComp->RegisterComponent();
}
