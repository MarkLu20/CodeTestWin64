// Fill out your copyright notice in the Description page of Project Settings.

#include "AliPayAPI.h"
#include "Json.h"
#include "ModuleManager.h"
//#include"Runtime/PacketHandlers/EncryptionComponents/AsymmetricEncryption/RSAEncryptionHandlerComponent/Public/RSAEncryptionHandlerComponent.h"
#include "Http.h"
UAliPayAPI *UAliPayAPI::AlipayInstance = nullptr;
UAliPayAPI * UAliPayAPI::GetAliPayInstance()
{
	if (AlipayInstance == nullptr)
	{
		AlipayInstance = NewObject<UAliPayAPI>();
		AlipayInstance->AddToRoot();
	}
	return AlipayInstance;
}

void UAliPayAPI::SetURL(FString URL)
{
	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(URL);
	HttpRequest->SetVerb(TEXT("GET"));
	HttpRequest->SetHeader(TEXT("Content-Type"), TEXT("application/json;charset=utf-8"));
	HttpRequest->OnProcessRequestComplete().BindUObject(this,&UAliPayAPI::RepquestCompelete);
	HttpRequest->OnRequestProgress().BindUObject(this,&UAliPayAPI::RequestProgress);
}

void UAliPayAPI::RepquestCompelete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded)
{

	UE_LOG(LogTemp,Error,TEXT("Alipay Websit"));
	//FRSAKeyAESEncryptionModuleInterface::IModuleInterface();
	
}


void UAliPayAPI::RequestProgress(FHttpRequestPtr HttpRequest, int32 Send, int32 DownLoad)
{
}

void UAliPayAPI::RSAEngory()
{
	FBitReader picketreader;
	FBitWriter picket;
	//FRSAEncryptorHandlerComponentModuleInterface *RSAModule = FModuleManager::GetModulePtr<FRSAEncryptorHandlerComponentModuleInterface>("RSAEncryptionHandlerComponent");
	//TSharedPtr<RSAKeyAESEncryptionHandlerComponent> RSAHandle = MakeShareable(new RSAKeyAESEncryptionHandlerComponent());
	//RSAHandle->Initialize();
	//if (RSAHandle->IsValid())
	//{
 //     
	//	/*RSAHandle->Incoming(picketreader);
	//	RSAHandle->Outgoing(picket);*/
	//	UE_LOG(LogTemp, Error, TEXT("Alipay Websit"));

	//}
}

