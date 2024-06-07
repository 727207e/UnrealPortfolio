// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/DataAttributeSet/EntityAttributeSet.h"
#include "Engine/DataTable.h"
#include "Data/DataAsset/UPBaseTable.h"
#include "GameplayEffectExtension.h"
#include "Tag/GameplayTags.h"
#include "Net/UnrealNetwork.h"
#include "Character/UPPlayerState.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"

UEntityAttributeSet::UEntityAttributeSet()
{
}

void UEntityAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute,  float& NewValue)
{
	if (Attribute == GetHpAttribute())
	{
		NewValue = FMath::Clamp(NewValue,  0.0f, GetMaxHp());
	}
}

bool UEntityAttributeSet::PreGameplayEffectExecute(FGameplayEffectModCallbackData& Data)
{
	return Super::PreGameplayEffectExecute(Data);
}

void UEntityAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if((GetHp() <= 0.0f) && !bOutOfHp)
	{
		Data.Target.AddLooseGameplayTag(TAG_CHARACTER_ISDEAD);
		OnDead.Broadcast();
	}

	bOutOfHp = (GetHp() <= 0.0f);
}

void UEntityAttributeSet::InitAttributeSet()
{
	SettingValue(GetTableData<FUPBaseTable>());
}


UAbilitySystemComponent* UEntityAttributeSet::GetOwningASC()
{
	IAbilitySystemInterface* ASCInterface;

	if (AActor* Owner = GetOwningActor())
	{
		if (AUPPlayerState* UPPlayerState = Cast<AUPPlayerState>(Owner))
		{
			APlayerController* ThePlayerController = Cast<APlayerController>(UPPlayerState->GetOwner());
			if (nullptr == ThePlayerController)
			{
				return nullptr;
			}
			ACharacter* TheCharacter = Cast<ACharacter>(ThePlayerController->GetPawn());
			if (nullptr == TheCharacter)
			{
				return nullptr;
			}
			ASCInterface = Cast<IAbilitySystemInterface>(TheCharacter);
			if (nullptr != ASCInterface)
			{
				return ASCInterface->GetAbilitySystemComponent();
			}
		}
		else
		{
			ASCInterface = Cast<IAbilitySystemInterface>(Owner);
			if (nullptr != ASCInterface)
			{
				return ASCInterface->GetAbilitySystemComponent();
			}
		}
	}
	return nullptr;
}

void UEntityAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION_NOTIFY(UEntityAttributeSet, Hp, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UEntityAttributeSet, MaxHp, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UEntityAttributeSet, Attack, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UEntityAttributeSet, AttackRange, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UEntityAttributeSet, AttackRadius, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UEntityAttributeSet, Armor, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UEntityAttributeSet, AttackSpeed, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UEntityAttributeSet, AttackRate, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UEntityAttributeSet, MovementSpeed, COND_None, REPNOTIFY_Always);
}

void UEntityAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
	if (UAbilitySystemComponent* ASC = GetOwningASC())
	{
		GAMEPLAYATTRIBUTE_REPNOTIFY(UEntityAttributeSet, Hp, OldHealth);
	}
}

void UEntityAttributeSet::OnRep_MaxHp(const FGameplayAttributeData& OldMaxHp)
{
	if (UAbilitySystemComponent* ASC = GetOwningASC())
	{
		GAMEPLAYATTRIBUTE_REPNOTIFY(UEntityAttributeSet, MaxHp, OldMaxHp);
	}
}

void UEntityAttributeSet::OnRep_Attack(const FGameplayAttributeData& OldAttack)
{
	if (UAbilitySystemComponent* ASC = GetOwningASC())
	{
		GAMEPLAYATTRIBUTE_REPNOTIFY(UEntityAttributeSet, Attack, OldAttack);
	}
}

void UEntityAttributeSet::OnRep_AttackRange(const FGameplayAttributeData& OldAttackRange)
{
	if (UAbilitySystemComponent* ASC = GetOwningASC())
	{
		GAMEPLAYATTRIBUTE_REPNOTIFY(UEntityAttributeSet, AttackRange, OldAttackRange);
	}
}

void UEntityAttributeSet::OnRep_AttackRadius(const FGameplayAttributeData& OldAttackRadius)
{
	if (UAbilitySystemComponent* ASC = GetOwningASC())
	{
		GAMEPLAYATTRIBUTE_REPNOTIFY(UEntityAttributeSet, AttackRadius, OldAttackRadius);
	}
}

void UEntityAttributeSet::OnRep_Armor(const FGameplayAttributeData& OldArmor)
{
	if (UAbilitySystemComponent* ASC = GetOwningASC())
	{
		GAMEPLAYATTRIBUTE_REPNOTIFY(UEntityAttributeSet, Armor, OldArmor);
	}
}

void UEntityAttributeSet::OnRep_AttackSpeed(const FGameplayAttributeData& OldAttackSpeed)
{
	if (UAbilitySystemComponent* ASC = GetOwningASC())
	{
		GAMEPLAYATTRIBUTE_REPNOTIFY(UEntityAttributeSet, AttackSpeed, OldAttackSpeed);
	}
}

void UEntityAttributeSet::OnRep_AttackRate(const FGameplayAttributeData& OldAttackRate)
{
	if (UAbilitySystemComponent* ASC = GetOwningASC())
	{
		GAMEPLAYATTRIBUTE_REPNOTIFY(UEntityAttributeSet, AttackRate, OldAttackRate);
	}
}

void UEntityAttributeSet::OnRep_MovementSpeed(const FGameplayAttributeData& OldMovementSpeed)
{
	if (UAbilitySystemComponent* ASC = GetOwningASC())
	{
		GAMEPLAYATTRIBUTE_REPNOTIFY(UEntityAttributeSet, MovementSpeed, OldMovementSpeed);
	}
}
