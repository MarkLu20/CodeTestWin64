// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "OpenLevel.generated.h"

/**
 * 
 */
UCLASS()
class CODETESTFORWINDOWS_API UOpenLevel : public UObject
{
	GENERATED_BODY()
		UOpenLevel(const FObjectInitializer &ObjectInitializer);
	
private:
	static UOpenLevel *OpenLevelInstance;
public:
	UFUNCTION(BlueprintCallable)
	void LoadPackageFunc(const FString &PackageName,int32 LoadFlags );
	UFUNCTION(BlueprintCallable)
	static UOpenLevel *GetOpenLevelInstance();
	UFUNCTION(BlueprintCallable)
	float GetLoadPercent(const FString &PackageName);
	float percent;
	UFUNCTION()
		void  LoadOver();
};
