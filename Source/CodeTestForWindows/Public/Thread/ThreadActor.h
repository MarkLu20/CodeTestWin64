// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RunnableThread.h"
#include "Runnable.h"
//#include "Run"
#include "ThreadActor.generated.h"
class FThreadTest :public FRunnable
{


public:
	virtual bool Init() override;


	virtual uint32 Run() override;


	virtual void Stop() override;


	virtual void Exit() override;

};

UCLASS()
class CODETESTFORWINDOWS_API AThreadActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AThreadActor();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	TQueue<FString> TestQue;
	
	
};
