#pragma once
#include "GameplayTagContainer.h"

#define TAG_PLAYER_INTERACTING_WITH_NPC FGameplayTag::RequestGameplayTag(FName("Player.State.InteractingWithNPC"))
#define TAG_ACTOR_INTERACTION FGameplayTag::RequestGameplayTag(FName("Actor.Action.Interaction"))
#define TAG_DATA_DAMAGE FGameplayTag::RequestGameplayTag(FName("Data.Damage"))