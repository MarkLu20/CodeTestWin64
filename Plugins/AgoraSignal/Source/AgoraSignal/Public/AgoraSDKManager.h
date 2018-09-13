// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AgoraSDKManager.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnReconnecting, int32, nretry);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnReconnected, int32, fd);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnLoginsuccess, int32, uid, int, fd);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLogin, int, Ecode);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLoginOut, int, Ecode);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLoginFailed, int, Ecode);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnChannelJoined, const FString, ChannelId, int32, ChannelIdSize);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnChannelLeaved, const FString, ChannelId, int32, ChannelIdSize);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnMessageSendSuccess, const FString, MessageID, int32, MessageIDSize);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FOnMessageInstantReceive, const FString, Accout, int32, AccountSize, int32, uid, const FString, Msg, int32, MsgSize);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_SevenParams(FOnMessageChannelReceive, const FString, ChannelID, int32, ChannelIDSize, const FString, Account, int32, AccountSize, int32, uid, const FString, Msg, int32, MsgSize);

UCLASS()
class AGORASIGNAL_API UAgoraSDKManager : public UObject
{
	GENERATED_BODY()
		UAgoraSDKManager(const FObjectInitializer &ObjectInitializer);
	
public:
	static UAgoraSDKManager *AgoraManagerInstance;
	UFUNCTION(BlueprintCallable,Category = "fire")
	static UAgoraSDKManager *GetAgoraSDKManagerInstance();
	UFUNCTION(BlueprintCallable)
	void Bind();
	class UUnrealSignal *UnrealSignalInstance;
	class UCallBack *CallBackInstance;
	TArray<FString> AccountArray;
	///UFUNCTION(BlueprintCallable,Category = "TextTest")
	
	TArray<FString> JoinedRoom;
	void CallBackSet();
	void InitData();
	TArray<FString> LoadAccout(FString Path);
	void Login(const FString AppID,const FString Accout,const FString Token,int32 uid,const FString DeviceID);
	void LoginOut();
	void MessageInstanSend(const FString Accout,int uid,const FString Msg,const FString MsgID);
	void ChannelJoin(const FString ChannelID);
	void ChannelLeave(const FString ChannelID);
	void MessageChannelSend(const FString ChannelID,const FString Msg,const FString MsgID);
	void GetAgroaInstance(FString AppId);





	UPROPERTY(BlueprintAssignable,BlueprintCallable, Category = "Agora")
		FOnReconnecting OnReconnecting;
	UPROPERTY(BlueprintAssignable, Category = "Agora")
		FOnReconnected OnReconnected;
	UPROPERTY(BlueprintAssignable, Category = "Agora")
		FOnLoginsuccess OnLoginsuccess;
	UPROPERTY(BlueprintAssignable, Category = "Agora")
		FOnLogin OnLogin;
	UPROPERTY(BlueprintAssignable, Category = "Agora")
		FOnLoginFailed OnLoginFailed;
	UPROPERTY(BlueprintAssignable, Category = "Agora")
		FOnChannelJoined OnChannelJoined;
	UPROPERTY(BlueprintAssignable, Category = "Agora")
		FOnChannelLeaved OnChannelLeaved;
	UPROPERTY(BlueprintAssignable, Category = "Agora")
		FOnMessageSendSuccess OnMessageSendSuccess;
	UPROPERTY(BlueprintAssignable, Category = "Agora")
		FOnMessageInstantReceive OnMessageInstantReceive;
	UPROPERTY(BlueprintAssignable, Category = "Agora")
		FOnMessageChannelReceive OnMessageChannelReceive;
	UPROPERTY(BlueprintAssignable, Category = "Agora")
		FOnLoginOut OnLoginOut;
private:
	UFUNCTION()
	void OnrenecCall(int32 par);

};
