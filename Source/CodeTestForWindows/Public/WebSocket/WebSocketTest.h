// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "WebSocketTest.generated.h"

/**
 * 
 */
class IWebSocket;
class IWebSocketsManager;
DECLARE_DELEGATE_OneParam(FMyIntDelegate, int32)
UCLASS()
class CODETESTFORWINDOWS_API UWebSocketTest : public UObject
{
	GENERATED_BODY()


public:
		UWebSocketTest(const FObjectInitializer &ObjectInitializer);

		TSharedRef<IWebSocket> CreateWebScoket(FString Url,  TArray<FString> Protocols, TMap<FString, FString> UpgradeHeaders = TMap<FString, FString>());
		void Closeoncet(const FString& Url, const TArray<FString>& Protocols, const TMap<FString, FString>& UpgradeHeaders = TMap<FString, FString>());
		bool Isoncet(const FString& Url, const TArray<FString>& Protocols, const TMap<FString, FString>& UpgradeHeaders = TMap<FString, FString>());
		void SetMessage(const FString &Message);
private:
	//TSharedRef<IWebSocket> WebSocketIntance;
	class FWebSocketsModule *WSModule =nullptr;
	TSharedPtr<IWebSocket> WebSocketPtr;
	FMyIntDelegate test;
public:
	UFUNCTION()
	void onErrorCB(const FString &ErrrorInfo);
	UFUNCTION()
	void onConnectedCB();
	UFUNCTION()
	void Closed(int32 StatusCode,const FString &Reason,bool bWasClean);
	UFUNCTION()
	void onMessageCB(const FString &MessageStr);
	//UFUNCTION()
		void OnRawMessageCB(const void * Data,SIZE_T Size,SIZE_T BytesRemaining);
	
};
