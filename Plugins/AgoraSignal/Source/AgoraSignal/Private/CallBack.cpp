// Fill out your copyright notice in the Description page of Project Settings.

#include "CallBack.h"
#include "Engine.h"
#include "FileHelper.h"
#include "Paths.h"
#include "UnrealSignal.h"
#include "AgoraSDKManager.h"
#include "ScopeLock.h"
UCallBack *UCallBack::CallBackInstance = nullptr;
UCallBack::UCallBack(const FObjectInitializer &ObjectInitializer):UObject(ObjectInitializer)
{
	SignalInstance = nullptr;
	AgoraSDKManagerInstance = nullptr;
	SignalInstance = UUnrealSignal::GetUnrealSignalInstance();
	AgoraSDKManagerInstance = UAgoraSDKManager::GetAgoraSDKManagerInstance();
	
}
UCallBack::~UCallBack()
{
}

UCallBack * UCallBack::GetCallBackInstance()
{
	FCriticalSection SynchronizationObject;
	if (CallBackInstance==nullptr)
	{
		FScopeLock Lock(&SynchronizationObject);
		if (CallBackInstance==nullptr)
		{
			CallBackInstance = NewObject<UCallBack>();
			CallBackInstance->AddToRoot();
		}
		
	}
	
	return CallBackInstance;
}

void UCallBack::SaveLog()
{ 
	//SaveLogB.AddDynamic(this, &UCallBack::SavelogFunction);
	//SaveLogB.Broadcast(LogTotal, path);
}

void UCallBack::onReconnecting(uint32_t nretry)
{
	GEngine->AddOnScreenDebugMessage(-1,10.0f,FColor::Blue,FString(TEXT("OnReconnecting")));
	AgoraSDKManagerInstance->OnReconnected.Broadcast(static_cast<int32>(nretry));
	
}

void UCallBack::onReconnected(int fd)
{
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Blue, FString(TEXT("OnReconnected")));
	AgoraSDKManagerInstance->OnReconnected.Broadcast(fd);
}

void UCallBack::onLoginSuccess(uint32_t uid, int fd)
{   
	AgoraSDKManagerInstance->OnLoginsuccess.Broadcast(static_cast<int32>(uid),fd);
	GEngine->AddOnScreenDebugMessage(-1,10.0f,FColor::Red,FString("Login Succes"));;
}

void UCallBack::onLogout(int ecode)
{
	AgoraSDKManagerInstance->OnLoginOut.Broadcast(ecode);
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, FString("Login Out"));;
}

void UCallBack::onLoginFailed(int ecode)
{
	AgoraSDKManagerInstance->OnLoginFailed.Broadcast(ecode);

	//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, FString("Login Failed"));;
}

void UCallBack::onChannelJoined(char const * channelID, size_t channelID_size)
{   
	AgoraSDKManagerInstance->OnChannelJoined.Broadcast(UTF8_TO_TCHAR(channelID),static_cast<int32>(channelID_size));
	FString Joined = UTF8_TO_TCHAR(channelID);
	AgoraSDKManagerInstance->JoinedRoom.Add(Joined);
	
	GEngine->AddOnScreenDebugMessage(-1,10.0f,FColor::Purple,FString("Joined"+Joined));
}

void UCallBack::onChannelJoinFailed(char const * channelID, size_t channelID_size, int ecode)
{

}

void UCallBack::onChannelLeaved(char const * channelID, size_t channelID_size, int ecode)
{

	FString Joined = UTF8_TO_TCHAR(channelID);
	if (AgoraSDKManagerInstance->JoinedRoom.Contains(Joined))
	{
		AgoraSDKManagerInstance->JoinedRoom.Remove(Joined);
	}

}

void UCallBack::onChannelUserJoined(char const * account, size_t account_size, uint32_t uid)
{
}

void UCallBack::onChannelUserLeaved(char const * account, size_t account_size, uint32_t uid)
{
}

void UCallBack::onChannelUserList(int n, char ** accounts, uint32_t * uids)
{
}

void UCallBack::onChannelQueryUserNumResult(char const * channelID, size_t channelID_size, int ecode, int num)
{
}

void UCallBack::onChannelQueryUserIsIn(char const * channelID, size_t channelID_size, char const * account, size_t account_size, int isIn)
{
}

void UCallBack::onChannelAttrUpdated(char const * channelID, size_t channelID_size, char const * name, size_t name_size, char const * value, size_t value_size, char const * type, size_t type_size)
{
}

void UCallBack::onInviteReceived(char const * channelID, size_t channelID_size, char const * account, size_t account_size, uint32_t uid, char const * extra, size_t extra_size)
{
}

void UCallBack::onInviteReceivedByPeer(char const * channelID, size_t channelID_size, char const * account, size_t account_size, uint32_t uid)
{
}

void UCallBack::onInviteAcceptedByPeer(char const * channelID, size_t channelID_size, char const * account, size_t account_size, uint32_t uid, char const * extra, size_t extra_size)
{
}

void UCallBack::onInviteRefusedByPeer(char const * channelID, size_t channelID_size, char const * account, size_t account_size, uint32_t uid, char const * extra, size_t extra_size)
{
}

void UCallBack::onInviteFailed(char const * channelID, size_t channelID_size, char const * account, size_t account_size, uint32_t uid, int ecode, char const * extra, size_t extra_size)
{
}

void UCallBack::onInviteEndByPeer(char const * channelID, size_t channelID_size, char const * account, size_t account_size, uint32_t uid, char const * extra, size_t extra_size)
{
}

void UCallBack::onInviteEndByMyself(char const * channelID, size_t channelID_size, char const * account, size_t account_size, uint32_t uid)
{
}

void UCallBack::onInviteMsg(char const * channelID, size_t channelID_size, char const * account, size_t account_size, uint32_t uid, char const * msgType, size_t msgType_size, char const * msgData, size_t msgData_size, char const * extra, size_t extra_size)
{
}

void UCallBack::onMessageSendError(char const * messageID, size_t messageID_size, int ecode)
{

}

void UCallBack::onMessageSendProgress(char const * account, size_t account_size, char const * messageID, size_t messageID_size, char const * type, size_t type_size, char const * info, size_t info_size)
{
}

void UCallBack::onMessageSendSuccess(char const * messageID, size_t messageID_size)
{
	//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, FString(UTF8_TO_TCHAR(messageID)));
	AgoraSDKManagerInstance->OnMessageSendSuccess.Broadcast(UTF8_TO_TCHAR(messageID),static_cast<int32>(messageID_size));

}

void UCallBack::onMessageAppReceived(char const * msg, size_t msg_size)
{
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, FString(ANSI_TO_TCHAR(msg)));
}

void UCallBack::onMessageInstantReceive(char const * account, size_t account_size, uint32_t uid, char const * msg, size_t msg_size)
{
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Green,FString(UTF8_TO_TCHAR(msg)));
	AgoraSDKManagerInstance->OnMessageInstantReceive.Broadcast(UTF8_TO_TCHAR(account),static_cast<int32>(account_size),static_cast<int32>(uid),UTF8_TO_TCHAR(msg),static_cast<int32>(msg_size));
}

void UCallBack::onMessageChannelReceive(char const * channelID, size_t channelID_size, char const * account, size_t account_size, uint32_t uid, char const * msg, size_t msg_size)
{
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Green, FString(UTF8_TO_TCHAR(msg)));
	AgoraSDKManagerInstance->OnMessageChannelReceive.Broadcast(UTF8_TO_TCHAR(channelID),static_cast<int32>(channelID_size),UTF8_TO_TCHAR(account),static_cast<int32>(account_size),static_cast<int32>(uid),UTF8_TO_TCHAR(msg),static_cast<int32>(msg_size));
}

void UCallBack::onLog(char const * txt, size_t txt_size)

{
	
	FString Log = UTF8_TO_TCHAR(txt);
	UE_LOG(LogTemp, Warning, TEXT("%s"),*Log);
	
	//GLog->Log
   
}

void UCallBack::onInvokeRet(char const * callID, size_t callID_size, char const * err, size_t err_size, char const * resp, size_t resp_size)
{
}

void UCallBack::onMsg(char const * from, size_t from_size, char const * t, size_t t_size, char const * msg, size_t msg_size)
{
}

void UCallBack::onUserAttrResult(char const * account, size_t account_size, char const * name, size_t name_size, char const * value, size_t value_size)
{
}

void UCallBack::onUserAttrAllResult(char const * account, size_t account_size, char const * value, size_t value_size)
{
}

void UCallBack::onError(char const * name, size_t name_size, int ecode, char const * desc, size_t desc_size)
{
}

void UCallBack::onQueryUserStatusResult(char const * name, size_t name_size, char const * status, size_t status_size)
{
}

void UCallBack::onDbg(char const * a, size_t a_size, char const * b, size_t b_size)
{
}

void UCallBack::onBCCall_result(char const * reason, size_t reason_size, char const * json_ret, size_t json_ret_size, char const * callID, size_t callID_size)
{
}

