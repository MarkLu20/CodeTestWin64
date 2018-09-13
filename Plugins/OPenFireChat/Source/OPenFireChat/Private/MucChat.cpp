// Fill out your copyright notice in the Description page of Project Settings.

#include "MucChat.h"
#include "OPenFireChatAPI.h"
#include "Runtime/Online/XMPP/Public/Xmpp.h"
#include "Http.h"
#include "Json.h"
#include "HttpManager.h"



UMucChat::UMucChat(const FObjectInitializer &ObjectInitializer):UObject(ObjectInitializer)
{
	OpenFireIntance = GetDefault<UOpenFireChatAPI>();
	OpenFireIntance->GetXmpptr.AddUObject(this,&UMucChat::GetXmppChatPtr);
	MucSymo = FString(L"B82137CB4410705988D6FCB2C43EBBB4 8fec252d4D9E7F56009C8C9Da669ad9A");
	
}

void UMucChat::GetXmppChatPtr(const IXmppChatPtr& xmppChatPtr)
{
	ChatPtr = xmppChatPtr;
}

void UMucChat::MucSendMessage(const FString& FromUser, const FString& Message, const FString &RoomName)
{
	if (OpenFireIntance->JoinedRoomArray.Num()>0)
	{

	
	FUser = FromUser;
	Msg = Message;
	MsgType = RoomName;
	
	
	
	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL("http://192.168.2.12:8083/api/getAllUserName");
	HttpRequest->SetVerb(TEXT("GET"));
	HttpRequest->SetHeader(TEXT("Content-Type"), TEXT("application/json;charset=utf-8"));
	HttpRequest->OnProcessRequestComplete().BindUObject(this, &UMucChat::RepquestCompelete);
	HttpRequest->ProcessRequest();
	}
	else
	{
		UE_LOG(LogTemp,Error,TEXT("Not Joinde Room"));
	}
}

void UMucChat::JoinMucRoom(const FString &RoomName)
{  
	OpenFireIntance->JoinRoomDel.Broadcast(RoomName);
	

}

void UMucChat::RepquestCompelete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded)
{    

	FXmppChatMessage ChatMessage;
	ChatMessage.FromJid.Id = FUser;
	
	FString Messge = Msg + MucSymo + MsgType;
	ChatMessage.Body = Messge;
	ChatMessage.Timestamp = FDateTime::Now();
	if (HttpResponse->GetResponseCode() == 200)
	{
		FString Content = HttpResponse->GetContentAsString();
		TArray<TSharedPtr<FJsonValue>> JsonParsed;
		TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(HttpResponse->GetContentAsString());
		if (FJsonSerializer::Deserialize(JsonReader, JsonParsed))
		{
			for (int32 i = 0; i < JsonParsed.Num(); ++i)
			{
				FString TUser;
				
				JsonParsed[i]->TryGetString(TUser);
				ChatMessage.ToJid.Id = TUser;
				ChatPtr->SendChat(FUser,ChatMessage);
			}

		}

	}
}


