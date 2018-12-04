// Fill out your copyright notice in the Description page of Project Settings.

#include "WebSocketTest.h"
#include "Engine.h"
#include "Runtime/Online/WebSockets/Public/WebSocketsModule.h"
#include "Runtime/Online/WebSockets/Public/IWebSocketsManager.h"
#include "Runtime/Online/WebSockets/Public/IWebSocket.h"
#include "ModuleManager.h"


 UWebSocketTest::UWebSocketTest(const FObjectInitializer &ObjectInitializer)
{
	 WSModule = FModuleManager::LoadModulePtr<FWebSocketsModule>("WebSockets");
}

 TSharedRef<IWebSocket> UWebSocketTest::CreateWebScoket( FString Url,  TArray<FString> Protocols,  TMap<FString, FString>  UpgradeHeaders /*= TMap<FString, FString>()*/)
 {
	 
	 //TSharedPtr<IWebSocketsManager> wsmanager = MakeShareable<IWebSocketsManager>(new IWebSocketsManager);
	 TArray<FString> TestWebStr;
	 TestWebStr.Add(TEXT("ws"));
	 TestWebStr.Add(TEXT("wss"));
	 //TestWebStr.Add(TEXT("v10.stomp"));
	 //TestWebStr.Add(TEXT("v11.stomp"));
	// TestWebStr.Add("Protocol");
	 //TestWebStr.Add("Protocol-v2");
	 //testWeb->CreateWebScoket(FString("wss://echo.websocket.org"),TestWebStr);
	 FString url = FString(L"ws://123.207.167.163:9010/ajaxchattest");
	 TSharedRef<IWebSocket> WebSocket = WSModule->CreateWebSocket(url);
	 WebSocketPtr = WebSocket;
	//WebSocket->
	// WebSocketIntance = WebSocket
	 //WebSocket->
	 WebSocketPtr->Connect();
	 WebSocketPtr->OnConnected().AddUObject(this,  &UWebSocketTest::onConnectedCB);
	
	 WebSocketPtr->OnClosed().AddUObject(this,&UWebSocketTest::Closed);
	WebSocket->OnConnectionError().AddUObject(this,&UWebSocketTest::onErrorCB);
	 //WebSocketPtr->OnClosed().AddUFunction(this,  FName("Closed"));
	 WebSocketPtr->OnMessage().AddUObject(this,&UWebSocketTest::onMessageCB);
	 WebSocketPtr->OnRawMessage().AddUObject(this,&UWebSocketTest::OnRawMessageCB);
	// WebSocket->Send(FString("hhahahahh ahaa "));
	 
	// WebSocket->Send("TestWebSocket");
	// WebSocket->Close();
	//return  TSharedRef<IWebSocket>();
	 return WebSocket;
	
 }



 void UWebSocketTest::Closeoncet(const FString& Url, const TArray<FString>& Protocols, const TMap<FString, FString>& UpgradeHeaders /*= TMap<FString, FString>()*/)
 {
	// TSharedRef<IWebSocket> WebSocket = WSModule->CreateWebSocket(Url, Protocols);
	 //WebSocketPtr->Close();
	 
 }

 bool UWebSocketTest::Isoncet(const FString& Url, const TArray<FString>& Protocols, const TMap<FString, FString>& UpgradeHeaders /*= TMap<FString, FString>()*/)
 {  
	 TSharedRef<IWebSocket> WebSocket = WSModule->CreateWebSocket(Url, Protocols);
	 return  WebSocket->IsConnected();
 }

 void UWebSocketTest::SetMessage(const FString &Message)
 {
	 //WebSocketPtr->Send(FString("hahahahhahahahahhhahahah"));
	 FTCHARToUTF8 Converted(*Message);
	 WebSocketPtr->Send((uint8*)Converted.Get(), Converted.Length(), true);
 }

 void UWebSocketTest::onErrorCB(const FString &ErrrorInfo)
 {
	 UE_LOG(LogTemp, Error, TEXT("OnConnectionError %s"), *ErrrorInfo);
 }

 void UWebSocketTest::onConnectedCB()
 {
	 UE_LOG(LogTemp, Error, TEXT("OnConnected"));
	
 }


 void UWebSocketTest::Closed(int32 StatusCode, const FString &Reason, bool bWasClean)
 {
	 UE_LOG(LogTemp, Error, TEXT("OnClosed %s,%d"),*Reason, StatusCode);
 }

 void UWebSocketTest::onMessageCB(const FString &MessageStr)
 {
	 UE_LOG(LogTemp, Error, TEXT("OnMessage %s"), *MessageStr);
 }

 void UWebSocketTest::OnRawMessageCB(const void * Data, SIZE_T Size, SIZE_T BytesRemaining)
 {
	 UE_LOG(LogTemp, Error, TEXT("OnMessage"));
 }
