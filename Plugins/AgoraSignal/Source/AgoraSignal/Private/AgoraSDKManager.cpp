// Fill out your copyright notice in the Description page of Project Settings.

#include "AgoraSDKManager.h"
#include "UnrealSignal.h"
#include "CallBack.h"
#include "ScopeLock.h"

UAgoraSDKManager *UAgoraSDKManager::AgoraManagerInstance = nullptr;
UAgoraSDKManager::UAgoraSDKManager(const FObjectInitializer &ObjectInitializer) :UObject(ObjectInitializer)
{
	UnrealSignalInstance = nullptr;
	CallBackInstance = nullptr;
	
	/*UnrealSignalInstance = UUnrealSignal::GetUnrealSignalInstance();
	CallBackInstance = UCallBack::GetCallBackInstance();
	*/
	/*AccountArray= UnrealSignalInstance->LoadAccount(FString(L"./OpenID/Account.json"));
	UnrealSignalInstance->GetAgroaInstance(FString(L"fb50b66cf43940679083c25b520192b0"));*/
	//UnrealSignalInstance->CallBackSet(CallBackInstance);
	//²âÊÔ
	/*UnrealSignalInstance->Login(FString(L"fb50b66cf43940679083c25b520192b0"), AccountArray[0], FString(L"_no_need_token"), 0, FString(""));*/
	

}

UAgoraSDKManager * UAgoraSDKManager::GetAgoraSDKManagerInstance()
{
	FCriticalSection SynchronizationObject;
	if (AgoraManagerInstance == nullptr)
	{
		FScopeLock Lock(&SynchronizationObject);
		if (AgoraManagerInstance==nullptr)
		{
			AgoraManagerInstance = NewObject<UAgoraSDKManager>();
			AgoraManagerInstance->AddToRoot();
		}
		
	}
	
	return AgoraManagerInstance;
}


void UAgoraSDKManager::Bind()
{
	AgoraManagerInstance->OnReconnecting.AddDynamic(this, &UAgoraSDKManager::OnrenecCall);
}

void UAgoraSDKManager::CallBackSet()
{
	
	UnrealSignalInstance->CallBackSet(CallBackInstance);
}

void UAgoraSDKManager::InitData()
{
	UnrealSignalInstance = UUnrealSignal::GetUnrealSignalInstance();
	CallBackInstance = UCallBack::GetCallBackInstance();
}

TArray<FString> UAgoraSDKManager::LoadAccout(FString Path)
{
	return UnrealSignalInstance->LoadAccount(Path);
}

void UAgoraSDKManager::GetAgroaInstance(FString AppId)
{
	UnrealSignalInstance->GetAgroaInstance(AppId);
}

void UAgoraSDKManager::OnrenecCall(int32 par)
{
	UE_LOG(LogTemp,Error,TEXT("%d"),par);
}

void UAgoraSDKManager::Login(const FString AppID, const FString Accout,  const FString Token, int32 uid, const FString DeviceID)
{
	UnrealSignalInstance->Login(AppID,Accout,Token,uid,DeviceID);
}

void UAgoraSDKManager::LoginOut()
{
	UnrealSignalInstance->LoginOut();
}

void UAgoraSDKManager::MessageInstanSend(const FString Accout, int uid, const FString Msg, const FString MsgID)
{
	UnrealSignalInstance->MessageInstanSend(Accout,uid,Msg,MsgID);
}

void UAgoraSDKManager::ChannelJoin(const FString ChannelID)
{
	UnrealSignalInstance->ChannelJoin(ChannelID);
}

void UAgoraSDKManager::ChannelLeave(const FString ChannelID)
{
	UnrealSignalInstance->ChanelLeave(ChannelID);
}

void UAgoraSDKManager::MessageChannelSend(const FString ChannelID, const FString Msg, const FString MsgID)
{
	UnrealSignalInstance->MessgeChannelSend(ChannelID,Msg,MsgID);
}


