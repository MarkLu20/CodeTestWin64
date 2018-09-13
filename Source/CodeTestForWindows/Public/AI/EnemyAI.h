// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAI.generated.h"

/**
 *
 */
UCLASS()
class CODETESTFORWINDOWS_API AEnemyAI : public AAIController
{
	GENERATED_BODY()
public:
	AEnemyAI();
	UPROPERTY(transient)
		class UBlackboardComponent *BlackboardComp;
	UPROPERTY(transient)
		class UBehaviorTreeComponent *BehaviorComp;

public:
	virtual void Possess(APawn* InPawn) override;
	uint8 EnemyKeyID;

};
