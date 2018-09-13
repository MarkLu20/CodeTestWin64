// Fill out your copyright notice in the Description page of Project Settings.

#include "UnrealSignal.h"
#include "Networking.h"
#include "stdio.h"
#include "stdlib.h"
#include "iostream"
#include "CallBack.h"
#include "Sockets.h"
#include "Json.h"
#include "Paths.h"
#include "FileHelper.h"
#include "ScopeLock.h"
using namespace std;
UUnrealSignal *UUnrealSignal::USInstance = nullptr;
UUnrealSignal::UUnrealSignal(const FObjectInitializer& ObjectInitializer)
{
	
}
UUnrealSignal::~UUnrealSignal()
{
}

void UUnrealSignal::Tick(float DeltaTime)
{
}

bool UUnrealSignal::IsTickable() const
{
	return true;
}

TStatId UUnrealSignal::GetStatId() const
{
	return TStatId();
}

UUnrealSignal * UUnrealSignal::GetUnrealSignalInstance()
{
	FCriticalSection SynchronizationObject;
	if (USInstance==nullptr)
	{
		FScopeLock Lock(&SynchronizationObject);
		if (USInstance==nullptr)
		{
			USInstance = NewObject<UUnrealSignal>();
			USInstance->AddToRoot();
		}
		
	}
	
	return USInstance;
}

void UUnrealSignal::GetAgroaInstance(const FString AppID)
{
	string Size;
	Size = TCHAR_TO_UTF8(*AppID);
	int b = Size.size();
	AgoraInstance = getAgoraSDKInstanceWin(TCHAR_TO_UTF8(*AppID),Size.size() );
	

}

void UUnrealSignal::CallBackSet(UCallBack *callBack)
{
	AgoraInstance->callbackSet(callBack);
}

void UUnrealSignal::Login(const FString AppID, const FString Account, const FString Token, int32 uid, const FString DeviceID)
{
	
	//AgoraInstance->login2(TCHAR_TO_ANSI(*AppID),AppID.GetAllocatedSize(),TCHAR_TO_ANSI(*Account),Account.GetAllocatedSize(),TCHAR_TO_ANSI(*Token),Token.GetAllocatedSize() ,static_cast<uint32>(uid),TCHAR_TO_ANSI(*DeviceID),DeviceID.GetAllocatedSize(),static_cast<size_t>(RetryTime),static_cast<size_t>(RetryCount));
	string Appidstring = TCHAR_TO_UTF8(*AppID);
	string Accountstring = TCHAR_TO_UTF8(*Account);
	string Tokenstring = TCHAR_TO_UTF8(*Token);
	string DeviceIDstring = TCHAR_TO_UTF8(*DeviceID);

	AgoraInstance->login(Appidstring.data(),Appidstring.size(), Accountstring.data(),Accountstring.size(),Tokenstring.data() ,Tokenstring.size(),static_cast<uint32>(uid),DeviceIDstring.data() ,DeviceIDstring.size());
	
	
	
}

void UUnrealSignal::LoginOut()
{
	AgoraInstance->logout();
}

void UUnrealSignal::MessageInstanSend(const FString account, int uid, const FString Msg, const FString MsgID)
{
	string accountString = TCHAR_TO_UTF8(*account);
	string msgString = TCHAR_TO_UTF8(*Msg);
	string msgIDString = TCHAR_TO_UTF8(*MsgID);
	AgoraInstance->messageInstantSend(accountString.data(),accountString.size(),static_cast<uint32>(uid),msgString.data(),msgString.size(),msgIDString.data(),msgIDString.size());

}

void UUnrealSignal::QureyUserStatus(const FString Account)
{
	string accoutString = TCHAR_TO_UTF8(*Account);
	AgoraInstance->queryUserStatus(accoutString.data(),accoutString.size());
}

void UUnrealSignal::ChannelJoin(const FString ChannelID)
{
	string ChannelIDString = TCHAR_TO_UTF8(*ChannelID);
	AgoraInstance->channelJoin(ChannelIDString.data(),ChannelIDString.size());
}

void UUnrealSignal::ChanelLeave(const FString ChanelID)
{
	string ChannelIDString = TCHAR_TO_UTF8(*ChanelID);
	AgoraInstance->channelLeave(ChannelIDString.data(),ChannelIDString.size());
}

void UUnrealSignal::ChannelQueryUserNum(const FString ChannelID)
{
	string ChannelIDString = TCHAR_TO_UTF8(*ChannelID);
	AgoraInstance->channelQueryUserNum(ChannelIDString.data(), ChannelIDString.size());
}

void UUnrealSignal::MessgeChannelSend(const FString ChannelID, const FString Msg, const FString MsgID)
{
	string ChanelIDstring = TCHAR_TO_UTF8(*ChannelID);
	string MsgString = TCHAR_TO_UTF8(*Msg);
	string MsgIDString = TCHAR_TO_UTF8(*MsgID);
	AgoraInstance->messageChannelSend(ChanelIDstring.data(),ChanelIDstring.size(),MsgString.data(),MsgString.size(),MsgIDString.data(),MsgIDString.size());
}

void UUnrealSignal::ChannelInviteUser(const FString ChannelID, const FString Account, int uid)
{
}

TArray<FString> UUnrealSignal::LoadAccount( FString Path)
{
	TArray<FString> TestArray;
	FString JsonValue;
	Path = FPaths::ProjectDir() / *Path;
	FFileHelper::LoadFileToString(JsonValue, *Path);
	TSharedPtr<FJsonObject> JsonObject;
	TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(JsonValue);
	bool BFlag = FJsonSerializer::Deserialize(JsonReader, JsonObject);
	FString Account = JsonObject->GetStringField("Account");
	FString OtherAccount = JsonObject->GetStringField("OtherAccount");
	TestArray.Add(Account);
	TestArray.Add(OtherAccount);

	return TestArray;
}

void UUnrealSignal::Test(int32 t)
{

}








