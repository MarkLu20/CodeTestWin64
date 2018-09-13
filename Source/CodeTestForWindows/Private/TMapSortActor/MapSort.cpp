// Fill out your copyright notice in the Description page of Project Settings.

#include "MapSort.h"


// Sets default values
AMapSort::AMapSort()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMapSort::BeginPlay()
{
	Super::BeginPlay();
	TMap<int32, int32> SortTest;
	SortTest.Add(1,5);
	SortTest.Add(4, 8);
	SortTest.Add(5, 578);
	SortTest.Add(6, 10);
	SortTest.Add(8, 10);

	SortTest.ValueSort([](int32  A, int32 B) {return A<B; });
	FString test;
	
}

// Called every frame
void AMapSort::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

