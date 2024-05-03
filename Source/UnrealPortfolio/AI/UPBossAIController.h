// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/UPEnemyAIController.h"
#include "UPBossAIController.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPORTFOLIO_API AUPBossAIController : public AUPEnemyAIController
{
	GENERATED_BODY()

public :
	AUPBossAIController();
	
//TASK
	//지정한 스킬 호출하는 task

//Task
	//스킬 사용하면 스킬 변경 및 타겟 변경

//ragne
	//지정한 스킬의 범위나 위치에 도달하도록 하는 task



};