// Fill out your copyright notice in the Description page of Project Settings.

#include "HttpRequest.h"
#include "HttpManager.h"




UHttpRequest::UHttpRequest()
{
}

UHttpRequest::~UHttpRequest()
{

}

void UHttpRequest::HttpRequest(const FString& ServerAddr, const FString& Verb, const FHttpRequestCompleteDelegate& HttpRequestCompleteDelegate, const FHttpRequestProgressDelegate& HttpRequestProgress, const FString& HeaderName, const FString& HeaderValue)
{
	HttpRequest(HeaderName, HeaderValue, ServerAddr, Verb);
	HttpRequestPtr->OnProcessRequestComplete() = HttpRequestCompleteDelegate;
	HttpRequestPtr->OnRequestProgress() = HttpRequestProgress;
	HttpRequestPtr->ProcessRequest();

}

void UHttpRequest::HttpRequest(const FString& HeaderName, const FString& HeaderValue, const FString& ServerAddr, const FString& Verb)
{
	TSharedRef<IHttpRequest> HttpRequestRef = FHttpModule::Get().CreateRequest();
	HttpRequestPtr = HttpRequestRef;
	if (!HeaderValue.IsEmpty())
	{
		HttpRequestPtr->SetHeader(HeaderName, HeaderValue);
	}
	HttpRequestPtr->SetVerb(Verb);
	HttpRequestPtr->SetURL(ServerAddr);
	FHttpModule::Get().GetHttpManager().AddRequest(HttpRequestPtr.ToSharedRef());

}

void UHttpRequest::HttpRequest(const FString& ServerAddr, const FString& Verb, TFunction<void(FHttpRequestPtr, FHttpResponsePtr, bool)> CallBackHttpComPleteFunction, TFunction<void(FHttpRequestPtr, int32, int32)> CallBackHttpProgressFunction, const FString& HeaderName, const FString& HeaderValue)
{
	HttpRequest(HeaderName, HeaderValue, ServerAddr, Verb);
	PrivateCallBackHttpProgressFunction = CallBackHttpProgressFunction;
	PrivateCompleteCallBackFunction = CallBackHttpComPleteFunction;
	HttpRequestPtr->OnProcessRequestComplete().BindUObject(this, &UHttpRequest::OnRepquestCompelete);
	HttpRequestPtr->OnRequestProgress().BindUObject(this, &UHttpRequest::OnRequestProgress);
	HttpRequestPtr->ProcessRequest();

}

void UHttpRequest::ShutDownRequest()
{
	if (HttpRequestPtr.IsValid())
	{
		HttpRequestPtr->CancelRequest();
		FHttpModule::Get().GetHttpManager().RemoveRequest(HttpRequestPtr.ToSharedRef());
		if (HttpRequestPtr->OnProcessRequestComplete().IsBound())
		{
			HttpRequestPtr->OnProcessRequestComplete().Unbind();
		}
		if (HttpRequestPtr->OnRequestProgress().IsBound())
		{
			HttpRequestPtr->OnRequestProgress().Unbind();
		}

	}
}

void UHttpRequest::OnRepquestCompelete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded)
{
	PrivateCompleteCallBackFunction(HttpRequest, HttpResponse, bSucceeded);
}

void UHttpRequest::OnRequestProgress(FHttpRequestPtr HttpRequest, int32 Uploaded, int32 Downloaded)
{
	PrivateCallBackHttpProgressFunction(HttpRequest, Uploaded, Downloaded);
}




