// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Http.h"
#include "UObject/NoExportTypes.h"
#include "HttpRequest.generated.h"

/**
 *
 */
UCLASS()
class BREAKPOINTRESUME_API UHttpRequest : public UObject
{
	GENERATED_BODY()
public:
	UHttpRequest();
	~UHttpRequest();
	void HttpRequest(const FString& ServerAddr, const FString& Verb, const FHttpRequestCompleteDelegate& HttpRequestCompleteDelegate, const FHttpRequestProgressDelegate& HttpRequestProgress = FHttpRequestProgressDelegate(), const FString& HeaderName = TEXT(""), const FString& HeaderValue = TEXT(""));
	void HttpRequest(const FString& ServerAddr, const FString& Verb, TFunction<void(FHttpRequestPtr, FHttpResponsePtr, bool)> CallBackHttpComPleteFunction, TFunction<void(FHttpRequestPtr, int32, int32)> CallBackHttpProgressFunction = TFunction<void(FHttpRequestPtr, int32, int32)>(), const FString& HeaderName = TEXT(""), const FString& HeaderValue = TEXT(""));
	void ShutDownRequest();
	


private:
	void HttpRequest(const FString& Accept, const FString& AcceptEncoding, const FString& ServerAddr, const FString& Verb);
	void OnRepquestCompelete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded);
	void OnRequestProgress(FHttpRequestPtr HttpRequest, int32 Uploaded, int32 Downloaded);

private:
	TSharedPtr<IHttpRequest> HttpRequestPtr;
	TFunction<void(FHttpRequestPtr, FHttpResponsePtr, bool)> PrivateCompleteCallBackFunction;
	TFunction<void(FHttpRequestPtr, int32, int32)> PrivateCallBackHttpProgressFunction;



};




