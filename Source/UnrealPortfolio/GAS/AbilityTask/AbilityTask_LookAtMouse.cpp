// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/AbilityTask/AbilityTask_LookAtMouse.h"
#include "defines/UPCollision.h"
#include "Kismet/KismetMathLibrary.h"
UAbilityTask_LookAtMouse::UAbilityTask_LookAtMouse()
{
}

UAbilityTask_LookAtMouse* UAbilityTask_LookAtMouse::CreateTask(UGameplayAbility* OwningAbility)
{
	UAbilityTask_LookAtMouse* NewTask = NewAbilityTask<UAbilityTask_LookAtMouse>(OwningAbility);
	return  NewTask;
}

void UAbilityTask_LookAtMouse::Activate()
{
	Super::Activate();
	LookAtMouse();
}

void UAbilityTask_LookAtMouse::LookAtMouse()
{
	//FHitResult HitResult;	
	//Cast<APawn>(GetAvatarActor())->GetLocalViewingPlayerController()->GetHitResultUnderCursorByChannel(static_cast<ETraceTypeQuery>(ECC_Visibility),true,HitResult);
	//HitResult.Location.Z = 0;
	//FVector ActorLocation =  GetAvatarActor()->GetActorLocation();
	//ActorLocation.Z = 0;
	//const FRotator TargetRotation =  UKismetMathLibrary::FindLookAtRotation(ActorLocation,HitResult.Location);
	//GetAvatarActor()->SetActorRotation(TargetRotation);
	
	bIsDone = true;
}
