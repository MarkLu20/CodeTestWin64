// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LuachuGameProcess.generated.h"

/**
 * 
 */
UCLASS()
class CODETESTFORWINDOWS_API ULuachuGameProcess : public UObject
{
public:
	GENERATED_BODY()

		ULuachuGameProcess(const FObjectInitializer &ObjectInitializer);
		/** Does the thing. */
	void ExcuteExe(const FString &path);
private:
	FString ProjectDir;
	FProcHandle ProHandle;
	
};
