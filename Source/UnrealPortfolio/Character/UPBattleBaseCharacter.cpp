// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/UPBattleBaseCharacter.h"
#include "AbilitySystemComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "UPPlayerState.h"
#include "Data/DataTable/UPActionTable.h"
#include "GAS/Actor/GameplayEventDataRequest.h"

AUPBattleBaseCharacter::AUPBattleBaseCharacter()
{
	ASC = nullptr;

	static::ConstructorHelpers::FObjectFinder<UDataTable> TableDataRef(TEXT("/Script/Engine.DataTable'/Game/Data/ActionTableData/DT_ActionData.DT_ActionData'"));
	if(TableDataRef.Object)
	{
		ActionDataTable = TableDataRef.Object;	
	}

	static::ConstructorHelpers::FObjectFinder<UNiagaraSystem> EffectRef(TEXT("/Script/Niagara.NiagaraSystem'/Game/DownloadAssets/SlashHitVFX/NS/NS_Hit_GroundCrack.NS_Hit_GroundCrack'"));
	if(EffectRef.Object)
	{
		Effect = EffectRef.Object;
	}
}

void AUPBattleBaseCharacter::SetDead()
{
	
}


void AUPBattleBaseCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	APlayerController* PlayerController = Cast<APlayerController>(NewController);
	if (PlayerController)
	{
		AUPPlayerState* PS = GetPlayerState<AUPPlayerState>();
		if (PS)
		{
			ASC = PS->GetAbilitySystemComponent();
			SetupASCHostPlayer(PS);
			PlayerController->ConsoleCommand(TEXT("showdebug abilitysystem"));
		}
	}

	else // AI Controller
	{
		if(HasAuthority())
		{
			SetupASCHostPlayer(this);
		}

		else
		{
			ServerASCSyncRequest();
		}
	}
}

void AUPBattleBaseCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	SetupASCClientPlayer();
}

void AUPBattleBaseCharacter::ServerASCSyncRequest_Implementation()
{
	//Need Refactoring 
	SetupASCHostPlayer(this);
}


void AUPBattleBaseCharacter::SetupASCHostPlayer(AActor* InOwnerActor)
{
	ASC->InitAbilityActorInfo(InOwnerActor, this);

	for (const auto& StartAbility : StartAbilities)
	{
		FGameplayAbilitySpec StartSpec(StartAbility);
		ASC->GiveAbility(StartSpec);
	}

	for (const auto& StartInputAbility : StartInputAbilities)
	{
		FGameplayAbilitySpec StartSpec(StartInputAbility.Value);
		StartSpec.InputID = StartInputAbility.Key;
		ASC->GiveAbility(StartSpec);
	}
}

void AUPBattleBaseCharacter::SetupASCClientPlayer()
{
	AUPPlayerState* PS = GetPlayerState<AUPPlayerState>();
	if (PS)
	{
		ASC = PS->GetAbilitySystemComponent();
		ASC->InitAbilityActorInfo(PS, this);
	}
}

UAnimMontage* AUPBattleBaseCharacter::GetComboActionMontage()
{
	if (ComboActionMontage)
	{
		return ComboActionMontage;
	}

	return nullptr;
}

void AUPBattleBaseCharacter::CallGAS(int32 GameplayAbilityInputId)
{
	FGameplayAbilitySpec* Spec = ASC->FindAbilitySpecFromInputID(GameplayAbilityInputId);
	if (Spec)
	{
		Spec->InputPressed = true;
		if (Spec->IsActive())
		{
			ASC->AbilitySpecInputPressed(*Spec);
		}
		else
		{
			ASC->TryActivateAbility(Spec->Handle);
		}
	}
}

void AUPBattleBaseCharacter::Hit(FVector TargetLocation, TObjectPtr<class AGameplayEventDataRequest> ActionData)
{
	LookTarget(TargetLocation);
	Knockback(ActionData);
	PlayHitAnimation();
}

void AUPBattleBaseCharacter::PlayHitAnimation()
{
	if(HitMontage)
	{
		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
		AnimInstance->Montage_Play(HitMontage);
	}
}

void AUPBattleBaseCharacter::Knockback(TObjectPtr<class AGameplayEventDataRequest> ActionData)
{
	const FText RowTableName = FText::FromName( ActionData->ActionRowName);
	const FString RowTableNameString = RowTableName.ToString();
	const TCHAR* RowTableNamePtr = *RowTableNameString;
	const FName NextSection = *FString::Printf(TEXT("%s%d"), RowTableNamePtr, ActionData->ActionId);
	if(const FUPActionTable* ActionTableData = ActionDataTable->FindRow<FUPActionTable>(FName(NextSection),TEXT("Finding Row")))
	{
		FVector BreakVector = GetActorForwardVector() * ActionTableData->NockbackDuration;
		BreakVector.X = BreakVector.X + ActionTableData->NockbackSize;
		BreakVector.Z = ActionTableData->NockbackUpSize;
		LaunchCharacter(BreakVector,true,false);
		EffectTest();
		
	}
}

void AUPBattleBaseCharacter::EffectTest()
{
	if(Effect)
	{
		//로케이션 기준
		//NiagaraComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), Effect, FVector::ZeroVector, FRotator::ZeroRotator, FVector::OneVector);

		//스켈레톤 기준
		FString SocketName = TEXT("hand_r");
		UNiagaraFunctionLibrary::SpawnSystemAttached(
			Effect,
			GetMesh(),
			*SocketName,
			FVector::ZeroVector,
			FRotator::ZeroRotator,
			EAttachLocation::KeepRelativeOffset,
			true);
	}
}


UAbilitySystemComponent* AUPBattleBaseCharacter::GetAbilitySystemComponent() const
{
	return ASC;
}

