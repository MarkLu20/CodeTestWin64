// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Http.h"
#include "HttpObject.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FJsonList
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite)
		FString Uid;
	UPROPERTY(BlueprintReadWrite)
		FString Userid;
	UPROPERTY(BlueprintReadWrite)
		FString UserName;
	UPROPERTY(BlueprintReadWrite)
		FString UserPWD;
	UPROPERTY(BlueprintReadWrite)
		FString ZoneMark;
};
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPassJosnData,const TArray<FJsonList>&,JsonList);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTestx, FString, TestString);
UCLASS(Blueprintable)
class CODETESTFORWINDOWS_API UHttpObject : public UObject
{
	GENERATED_BODY()

public:
	
		UFUNCTION(BlueprintCallable)
		void SetUrl(FString ServerAddr);
		void RepquestCompelete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded);
		void PostRepquestCompelete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded);
		
		UPROPERTY(BlueprintAssignable)
			FPassJosnData PassJsonData;
		UPROPERTY(BlueprintAssignable)
			FTestx test;
		UFUNCTION(BlueprintCallable)
			static	UHttpObject* GetHttpObject();
		UFUNCTION(BlueprintImplementableEvent,BlueprintCallable)
			void GetURLData(TArray<FJsonList> &jsonlist);
		UFUNCTION(BlueprintCallable)
			void ShutDownHttpThread();
private:
		static UHttpObject *httpObject;
		UHttpObject *HttpObject = nullptr;
		  UHttpObject* const p =HttpObject;
};
