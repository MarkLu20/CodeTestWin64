// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BlackboardData.h"
#include "EnemyBlackboardData.generated.h"

/**
 * 
 */
UCLASS(BlueprintType,Blueprintable)
class CODETESTFORWINDOWS_API UEnemyBlackboardData : public UBlackboardData
{
	GENERATED_BODY()

public:
		UEnemyBlackboardData(const FObjectInitializer &ObjectInitializer);
	
};
