// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AliPayAPI.generated.h"

/**
 * 
 */
typedef TSharedPtr<class IHttpRequest> FHttpRequestPtr;
typedef TSharedPtr<class IHttpResponse, ESPMode::ThreadSafe> FHttpResponsePtr;
UCLASS()
class ALIPAY_API UAliPayAPI : public UObject
{
	GENERATED_BODY()
		UFUNCTION(BlueprintCallable,Category =Pay)
		static UAliPayAPI *GetAliPayInstance();
	UFUNCTION(BlueprintCallable, Category = Pay)
		void SetURL(FString URL);
	void RepquestCompelete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded);
	void RequestProgress(FHttpRequestPtr HttpRequest, int32 Send, int32 DownLoad);
	UFUNCTION(BlueprintCallable)
	void RSAEngory();
	
private:
	static UAliPayAPI *AlipayInstance;
};
