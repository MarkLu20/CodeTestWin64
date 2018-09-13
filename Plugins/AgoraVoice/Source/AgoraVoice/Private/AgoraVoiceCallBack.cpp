// Fill out your copyright notice in the Description page of Project Settings.

#include "AgoraVoiceCallBack.h"
#include "ScopeLock.h"
#include "AgoraVoiceManager.h"


UAgoraVoiceCallBack *UAgoraVoiceCallBack::AgoraVoiceCBInstance = nullptr;
UAgoraVoiceCallBack::UAgoraVoiceCallBack(const FObjectInitializer &ObjectInitializer) :UObject(ObjectInitializer)
{
	AgoraVoiceManager = GetDefault<UAgoraVoiceManager>();
}

UAgoraVoiceCallBack * UAgoraVoiceCallBack::GetAgoraVoiceCBInstance()
{
	FCriticalSection CriticalSection;
	if (AgoraVoiceCBInstance == nullptr)
	{
		FScopeLock Lock(&CriticalSection);
		if (AgoraVoiceCBInstance == nullptr)
		{
			AgoraVoiceCBInstance = NewObject<UAgoraVoiceCallBack>();
			AgoraVoiceCBInstance->AddToRoot();
		}
	}
	return AgoraVoiceCBInstance;
}

void UAgoraVoiceCallBack::onActiveSpeaker(uid_t uid)
{
	
}

void UAgoraVoiceCallBack::onError(int err, const char* msg)
{
	FString Log = UTF8_TO_TCHAR(msg);
	UE_LOG(LogTemp,Error,TEXT("%d"), err);
}

void UAgoraVoiceCallBack::onJoinChannelSuccess(const char* channel, uid_t uid, int elapsed)
{
	UE_LOG(LogTemp, Warning, TEXT("onJoinChannelSuccess"));
	AgoraVoiceManager->JoinSuccessDel.Broadcast(UTF8_TO_TCHAR(channel),static_cast<int32>(uid));
}

void UAgoraVoiceCallBack::onLeaveChannel(const RtcStats& stats)
{
	UE_LOG(LogTemp, Warning, TEXT("onLeaveChannel"));
}

void UAgoraVoiceCallBack::onRejoinChannelSuccess(const char* channel, uid_t uid, int elapsed)
{

	UE_LOG(LogTemp, Warning, TEXT("erew"));
}

void UAgoraVoiceCallBack::onUserJoined(uid_t uid, int elapsed)
{
	
}

void UAgoraVoiceCallBack::onWarning(int warn, const char* msg)
{
	FString Log = UTF8_TO_TCHAR(msg);
	UE_LOG(LogTemp, Warning, TEXT("%s"), UTF8_TO_TCHAR(*Log));
}

void UAgoraVoiceCallBack::onUserOffline(uid_t uid, USER_OFFLINE_REASON_TYPE reason)
{
	
}

void UAgoraVoiceCallBack::onConnectionBanned()
{
	UE_LOG(LogTemp, Warning, TEXT("onConnectionBanned"));
}

void UAgoraVoiceCallBack::onConnectionInterrupted()
{
	UE_LOG(LogTemp, Warning, TEXT("gergreg"));
}

void UAgoraVoiceCallBack::onConnectionLost()
{
	UE_LOG(LogTemp, Warning, TEXT("fgsfdgsdf"));
}

void UAgoraVoiceCallBack::onLastmileQuality(int quality)
{
	
}

void UAgoraVoiceCallBack::onNetworkQuality(uid_t uid, int txQuality, int rxQuality)
{
	
}

void UAgoraVoiceCallBack::onUserMuteAudio(uid_t uid, bool muted)
{
	
}
