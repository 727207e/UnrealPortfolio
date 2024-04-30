// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/UPBattleBaseCharacter.h"
#include "AbilitySystemComponent.h"
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

	bCanAttack = true;
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
	UsingGAArray.Add(*Spec);

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

TArray<FGameplayAbilitySpec> AUPBattleBaseCharacter::GetUsingGas(int32 GameplayAbilityInputId)
{
	TArray<FGameplayAbilitySpec> Result;

	for (FGameplayAbilitySpec GASpec : UsingGAArray)
	{
		if (GASpec.InputID == GameplayAbilityInputId)
		{
			Result.Add(GASpec);
		}
	}

	return Result;
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

	OnHitDelegate.Broadcast();
	OnHitDelegate.Clear();
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
	}
}

void AUPBattleBaseCharacter::SetAttackDelay(float DelayTime)
{
	UE_LOG(LogTemp, Log, TEXT("Timer Start %f"), DelayTime);
	GetWorld()->GetTimerManager().SetTimer(AttackDelay, FTimerDelegate::CreateLambda([=, this] 
		{
			UE_LOG(LogTemp, Log, TEXT("Timer Done"));
			bCanAttack = true;
		}), DelayTime, false);
}

void AUPBattleBaseCharacter::AttackEndCallBack()
{
	OnEndAttackDelegate.Broadcast();
	OnEndAttackDelegate.Clear();
}

void AUPBattleBaseCharacter::AddAttackEndCallBack(const FOnEndAttackDelegate& OnEndAttack)
{
	OnEndAttackDelegate = OnEndAttack;
}

void AUPBattleBaseCharacter::NormalAttack()
{
	
}

void AUPBattleBaseCharacter::AddOnEndAttackDelegate(FOnEndAttackDelegate& Delegate)
{
	OnEndAttackDelegate.AddLambda([&]()
		{
			Delegate.Broadcast();
			Delegate.Clear();
		});
}

void AUPBattleBaseCharacter::AddOnHitDelegate(FOnHitDelegate& Delegate)
{
	OnHitDelegate.AddLambda([&]()
		{
			Delegate.Broadcast();
			Delegate.Clear();
		});
}

UAbilitySystemComponent* AUPBattleBaseCharacter::GetAbilitySystemComponent() const
{
	return ASC;
}