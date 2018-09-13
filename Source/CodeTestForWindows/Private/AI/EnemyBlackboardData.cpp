// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyBlackboardData.h"



UEnemyBlackboardData::UEnemyBlackboardData(const FObjectInitializer &ObjectInitializer)
{

	FBlackboardEntry Target;
	Target.EntryName = FName("Target");
	//UBlackboardKeyType type;

	//Target.bInstanceSynced;
	//Target.KeyType = &type;
	Keys.Add(Target);
}
