// Fill out your copyright notice in the Description page of Project Settings.

#include "HttpObject.h"
#include "Json.h"
#include "HttpManager.h"
#define LOCTEXT_NAMESPACE "UHTTPOBJECT" 
UHttpObject* UHttpObject::httpObject = nullptr;
void UHttpObject::SetUrl(FString ServerAddr)
{
	HttpObject = NewObject<UHttpObject>();
	//p = NewObject<UHttpObject>();
	//p= NewObject<UHttpObject>();*/
	HttpObject->AddToRoot();


	 TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	//添加到HTTPMangerThread线程中
	 FHttpModule::Get().GetHttpManager().AddRequest(HttpRequest);
	
	HttpRequest->SetURL(ServerAddr);
	HttpRequest->SetVerb(TEXT("GET"));
	//HttpRequest->SetHeader(TEXT("User-Agent"), TEXT("X-UnrealEngine-Agent"));
	HttpRequest->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	//HttpRequest->SetHeader(TEXT("Accepts"), TEXT("application/json"));
	//HttpRequest->SetContentAsString(ServerAddr);
	HttpRequest->OnProcessRequestComplete().BindUObject(this,&UHttpObject::RepquestCompelete);
	HttpRequest->ProcessRequest();
	//FHttpModule::Get().GetHttpManager().Initialize();
	
}

void UHttpObject::RepquestCompelete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded)
{
	//httpObject->RemoveFromRoot();
	FText SS = LOCTEXT("中俄无奈", "中文");
	FString Content = HttpResponse->GetContentAsString();
	if (bSucceeded)
	{
		 int32 code=HttpResponse->GetResponseCode();
		TArray<FJsonList> jsonList;
		FJsonList jsondata;
		TArray<TSharedPtr<FJsonValue>> JsonParsed;
		TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(HttpResponse->GetContentAsString());
		if (FJsonSerializer::Deserialize(JsonReader, JsonParsed))
		{
			for (size_t i = 0; i < JsonParsed.Num(); i++)
			{
				jsondata.Uid = FString::FromInt(JsonParsed[i]->AsObject()->GetIntegerField("uid"));
				jsondata.Userid = JsonParsed[i]->AsObject()->GetStringField("userid");
				jsondata.UserName = JsonParsed[i]->AsObject()->GetStringField("username");
				jsondata.UserPWD = JsonParsed[i]->AsObject()->GetStringField("userpwd");
				jsondata.ZoneMark = JsonParsed[i]->AsObject()->GetStringField("zonemark");
				jsonList.Add(jsondata);
				
			}
			PassJsonData.Broadcast(jsonList);
			//test.Broadcast(FString(TEXT("sadfasdfasdfasdfasdf")));
			GetURLData(jsonList);
			
		}
		
		
		//SS = TCHAR_TO_UTF8(*SS);
		//FText aa= FText::FromString(SS);
		UE_LOG(LogTemp, Error, TEXT("******************"));
	}
}

void UHttpObject::PostRepquestCompelete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded)
{
}

UHttpObject * UHttpObject::GetHttpObject()
{
	if (httpObject == nullptr)
	{
		httpObject = NewObject<UHttpObject>();
		httpObject->AddToRoot();
	}
	return httpObject;
}
void UHttpObject::ShutDownHttpThread()
{  //关闭http模块
	FHttpModule::Get().GetHttpManager().Flush(true);
}
#undef LOCTEXT_NAMESPACE 
