// Fill out your copyright notice in the Description page of Project Settings.

#include "EmemyChracter.h"
#include "Runtime/AIModule/Classes/BehaviorTree/BehaviorTree.h"
#include "EnemyAI.h"

// Sets default values
AEmemyChracter::AEmemyChracter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AIControllerClass = AEnemyAI::StaticClass();

}

// Called when the game starts or when spawned
void AEmemyChracter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEmemyChracter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEmemyChracter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

