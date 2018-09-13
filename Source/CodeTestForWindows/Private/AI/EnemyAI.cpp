// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyAI.h"
#include "Runtime/GameplayTasks/Public/GameplayTasksModule.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "EmemyChracter.h"


AEnemyAI::AEnemyAI()
{
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));
	BehaviorComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorComp"));
	//this->runb
}

void AEnemyAI::Possess(APawn* InPawn)
{
	Super::Possess(InPawn);
	AEmemyChracter *Char = Cast<AEmemyChracter>(InPawn);
	if (Char &&Char->BotBehavior)
	{
		BlackboardComp->InitializeBlackboard(*(Char->BotBehavior->BlackboardAsset));
		//»ñÈ¡ºÚ°åµÄkey
		EnemyKeyID = BlackboardComp->GetKeyID("Target");
		FBlackboard::FKey TargetKey;
		TargetKey = BlackboardComp->GetKeyID("Target");
		BehaviorComp->StartTree(*Char->BotBehavior);
		
	}
	
}
