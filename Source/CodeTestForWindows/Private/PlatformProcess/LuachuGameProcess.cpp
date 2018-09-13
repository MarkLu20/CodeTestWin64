// Fill out your copyright notice in the Description page of Project Settings.

#include "LuachuGameProcess.h"
#include "Runtime/Core/Public/HAL/PlatformProcess.h"
#include "Paths.h"



ULuachuGameProcess::ULuachuGameProcess(const FObjectInitializer &ObjectInitializer) :UObject(ObjectInitializer)
{
	ProjectDir = FPaths::ProjectDir();
}

void ULuachuGameProcess::ExcuteExe(const FString & path)
{
	FString ExePath = ProjectDir + *path;
	FString error;
	const TCHAR *Path = ExePath.GetCharArray().GetData();
	uint32 OutProcessID;
	int32 PriorityModifier = 2;

	if (!ProHandle.IsValid()||!FPlatformProcess::IsProcRunning(ProHandle))
	{
		ProHandle = FPlatformProcess::CreateProc(Path, nullptr, true, false, false, &OutProcessID, PriorityModifier, nullptr, nullptr);
	}
	
		

	
	
	//FPlatformProcess::LaunchURL(Path,nullptr,&error);
}
