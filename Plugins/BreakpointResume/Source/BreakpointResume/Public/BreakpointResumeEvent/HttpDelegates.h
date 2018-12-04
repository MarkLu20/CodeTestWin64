// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DelegateCombinations.h"
#include "HttpDelegates.generated.h"

/**
 *
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGetDownLoadPercentage, float, Percentage);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGetDownLoadTotalSize, int32, TotalSize);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDownLoadDone);
UCLASS(BlueprintType)
class BREAKPOINTRESUME_API UHttpDelegates : public UObject
{
	GENERATED_BODY()

public:
	UHttpDelegates();

	UPROPERTY(BlueprintAssignable, Category = HttpDelegates)
		FGetDownLoadPercentage GetDownLoadPercentageDel;
	UPROPERTY(BlueprintAssignable, Category = HttpDelegates)
		FDownLoadDone  DownLoadDoneDel;
	UPROPERTY(BlueprintAssignable, Category = HttpDelegates)
		FGetDownLoadTotalSize GetDownLoadRemoteSize;

};
