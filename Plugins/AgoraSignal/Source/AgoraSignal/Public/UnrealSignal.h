// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <stdio.h>
#include <string.h>
#include "agora_sig.h"
#include "UObject/NoExportTypes.h"
#include "Runtime/Engine/Public/Tickable.h"
#include "UnrealSignal.generated.h"
using namespace agora_sdk_win;

/**
 *
 */
//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnReconnecting,int32,nretry);
//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnReconnected,int32,fd);
//DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnLoginsuccess,int32,uid,int,fd);
//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLogin,int,Ecode);
//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLoginOut, int, Ecode);
//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLoginFailed,int,Ecode);
//DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnChannelJoined,const FString ,ChannelId,int32,ChannelIdSize);
//DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnChannelLeaved, const FString, ChannelId, int32, ChannelIdSize);
//
//DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnMessageSendSuccess,const FString,MessageID,int32,MessageIDSize);
//DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FOnMessageInstantReceive,const FString,Accout,int32,AccountSize,int32,uid,const FString,Msg,int32,MsgSize);
//DECLARE_DYNAMIC_MULTICAST_DELEGATE_SevenParams(FOnMessageChannelReceive,const FString,ChannelID,int32,ChannelIDSize,const FString,Account,int32,AccountSize,int32,uid,const FString,Msg,int32,MsgSize);
//
UCLASS(Blueprintable)
class AGORASIGNAL_API UUnrealSignal : public UObject, public FTickableGameObject
{
	GENERATED_BODY()
public:
	UUnrealSignal(const FObjectInitializer& ObjectInitializer);
	~UUnrealSignal();

	// 通过 FTickableGameObject 继承
	virtual void Tick(float DeltaTime) override;

	virtual bool IsTickable() const override;

	virtual TStatId GetStatId() const override;
	//获取UnrealSignal实例
	UFUNCTION(BlueprintCallable, Category = "Agora")
		static UUnrealSignal *GetUnrealSignalInstance();
	//获取AgoraAPI实例
	UFUNCTION(BlueprintCallable, Category = "Agora")
		void GetAgroaInstance(const FString AppID);
	//设置回调对象
	UFUNCTION(BlueprintCallable, Category = "Agora")
		void CallBackSet(class UCallBack *callBack);
	//登录信令系统
	UFUNCTION(BlueprintCallable, Category = "Agora")
		void Login(const FString AppID,  const FString Account, const FString Token,  int32 uid, const FString DeviceID);
	//登出信令系统
	UFUNCTION(BlueprintCallable, Category = "Agora")
		void LoginOut();
	//发送点对点消息 (messageInstantSend)
	//该方法发送点对点消息到某个指定账号。 发送成功本地将回调 onMessageSendSuccess，
	//对方将收到 onMessageInstantReceive 回调。 发送失败将回调 onMessageSendError。
	UFUNCTION(BlueprintCallable, Category = "Agora")
		void MessageInstanSend(const FString account, int uid, const FString Msg, const FString MsgID);
	//查询用户状态 (queryUserStatus)
		//该方法用于查询用户是否在线。调用成功将触发 onQueryUserStatusResult 回调。
	UFUNCTION(BlueprintCallable, Category = "Agora")
		void QureyUserStatus(const FString Account);
	//加入频道 (channelJoin)
	//该方法让用户加入指定频道。用户一次只能加入一个频道。如加入指定频道时已在其他频道中，将自动从其他频道退出。 
	//用户加入频道成功后，自己将收到回调 onChannelJoined，其他同一频道内用户将收到回调 onChannelUserJoined。
	//用户加入失败后，自己将收到回调 onChannelJoinFailed。
	UFUNCTION(BlueprintCallable, Category = "Agora")
		void ChannelJoin(const FString ChannelID);
	UFUNCTION(BlueprintCallable, Category = "Agora")
		void ChanelLeave(const FString ChanelID);
	//查询频道用户数 (channelQueryUserNum)
	UFUNCTION(BlueprintCallable, Category = "Agora")
		void ChannelQueryUserNum(const FString ChannelID);
	//发送频道消息 (messageChannelSend)
	//该方法用于发送频道消息，频道内所有成员会收到 onMessageChannelReceive 回调。 发送成功会回调 onMessageSendSuccess，发送失败会回调 onMessageSendError。
	UFUNCTION(BlueprintCallable, Category = "Agora")
		void MessgeChannelSend(const FString ChannelID,const FString Msg,const FString MsgID);
	//发起呼叫 (channelInviteUser)
	//如果收到对方的确认信息，本地将回调 onInviteReceivedByPeer, 对方会回调 onInviteReceived。
	UFUNCTION(BlueprintCallable, Category = "Agora")
		void ChannelInviteUser(const FString ChannelID,const FString Account,int uid);
	UFUNCTION(BlueprintCallable, Category = "JsonTool")
		TArray<FString>  LoadAccount(FString Path);
	/*UPROPERTY(BlueprintAssignable, Category = "Agora")
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
        FOnLoginOut OnLoginOut;*/
	UFUNCTION(BlueprintCallable, Category = "Agora")
		void Test(int32 t);
private:
	static UUnrealSignal *USInstance;
	 IAgoraAPI *AgoraInstance= nullptr;
	
};



