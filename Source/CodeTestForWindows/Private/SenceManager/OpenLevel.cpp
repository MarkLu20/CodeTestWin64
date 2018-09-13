// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenLevel.h"

UOpenLevel *UOpenLevel::OpenLevelInstance = nullptr;
UOpenLevel::UOpenLevel(const FObjectInitializer &ObjectInitializer) : UObject(ObjectInitializer)
{


}

void UOpenLevel::LoadPackageFunc( const FString &PackageName, int32 LoadFlags)
{
	LoadPackage(NULL, L"/Game/Maps/ThirdPersonExampleMap",LOAD_None);
	
}

UOpenLevel * UOpenLevel::GetOpenLevelInstance()
{
	if (OpenLevelInstance == nullptr)
	{
		OpenLevelInstance = NewObject<UOpenLevel>();
		OpenLevelInstance->AddToRoot();
	}
	return OpenLevelInstance;
}

float UOpenLevel::GetLoadPercent(const FString &PackageName)
{
	percent = GetAsyncLoadPercentage(L"/Game/Maps/ThirdPersonExampleMap");
	if (percent ==0.5f)
	{
		UE_LOG(LogTemp,Error,TEXT("fsadfasdfasdfa"));
	}
	return percent;
}

void UOpenLevel::LoadOver()
{
	UE_LOG(LogTemp,Error,TEXT("Over"));
}


