// Fill out your copyright notice in the Description page of Project Settings.

#include "ThreadActor.h"
#include "ThreadManager.h"
#include "Queue.h"

// Sets default values
AThreadActor::AThreadActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//TQueue TestQue;
	
	TestQue.Enqueue(FString("1"));
	TestQue.Enqueue(FString("2"));
	TestQue.Enqueue(FString("3"));
	TestQue.Enqueue(FString("3"));
	

}

// Called when the game starts or when spawned
void AThreadActor::BeginPlay()
{
	Super::BeginPlay();
	FThreadTest *ThreadTest = new FThreadTest();
	FRunnableThread *Runnabletest= FRunnableThread::Create(ThreadTest,TEXT("TEST"));
	Runnabletest->WaitForCompletion();
	//FThreadManager::re
	/*FThreadManager::Get().AddThread(1,Runnabletest);
	FThreadManager::Get().RemoveThread(Runnabletest);*/
	delete Runnabletest;
	Runnabletest = nullptr;
	//testque
	TQueue<int32> TestIntQue;
	TestIntQue.Enqueue(1);
	TestIntQue.Enqueue(2);
	TestIntQue.Enqueue(3); 
	TestIntQue.Enqueue(4);
	int32 front;
	TestIntQue.Dequeue(front);
	UE_LOG(LogTemp, Error, TEXT("%d"), front);

	
	
	
	

	
}

// Called every frame
void AThreadActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	

}

bool FThreadTest::Init()
{
	return true;
}

uint32 FThreadTest::Run()
{
	for (int32 i = 0; i < 100; i++)
	{
		UE_LOG(LogTemp,Error,TEXT("%d"),i);
	}
	return 0;
}

void FThreadTest::Stop()
{
	
}

void FThreadTest::Exit()
{
	UE_LOG(LogTemp, Error, TEXT("ExitRunable"));
}
