#pragma once
#include "GameplayTagContainer.h"

#define TAG_PLAYER_INTERACTING_WITH_NPC FGameplayTag::RequestGameplayTag(FName("Player.State.InteractingWithNPC"))
#define TAG_ACTOR_INTERACTION FGameplayTag::RequestGameplayTag(FName("Actor.Action.Interaction"))
#define TAG_DATA_DAMAGE FGameplayTag::RequestGameplayTag(FName("Data.Damage"))
#define TAG_DATA_USE_MP FGameplayTag::RequestGameplayTag(FName("Data.UseMp"))
#define TAG_CHARACTER_ISDEAD FGameplayTag::RequestGameplayTag(FName("Character.State.IsDead"))
#define TAG_CHARACTER_BOSS_IS_DEAD FGameplayTag::RequestGameplayTag(FName("Character.State.BossIsDead"))
#define TAG_CHARACTER_SKILL FGameplayTag::RequestGameplayTag(FName("Character.Action.Skill"))
#define TAG_COUNTER_ATTACK FGameplayTag::RequestGameplayTag(FName("Character.Action.CounterAttackPosible"))
#define TAG_COUNTER_HIT FGameplayTag::RequestGameplayTag(FName("Character.Action.CounterHitPosible"))

#define TAG_HITGROUND FGameplayTag::RequestGameplayTag(FName("GameplayCue.Effect.BombExplore"))
#define TAG_FIREBUFF FGameplayTag::RequestGameplayTag(FName("GameplayCue.Effect.FireBuff"))