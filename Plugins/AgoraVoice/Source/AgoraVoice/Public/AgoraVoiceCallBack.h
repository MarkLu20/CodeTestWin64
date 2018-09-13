// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "IAgoraRtcEngine.h"
#include "AgoraVoiceCallBack.generated.h"
using namespace agora;
using namespace rtc;

/**
 * 
 */
class UAgoraVoiceManager;
UCLASS()
class AGORAVOICE_API UAgoraVoiceCallBack : public UObject , public IRtcEngineEventHandler
{
	GENERATED_BODY()
	
public:
	UAgoraVoiceCallBack(const FObjectInitializer &ObjectInitializer);
	
	static UAgoraVoiceCallBack *GetAgoraVoiceCBInstance();


	virtual void onActiveSpeaker(uid_t uid) override;


	virtual void onError(int err, const char* msg) override;


	virtual void onJoinChannelSuccess(const char* channel, uid_t uid, int elapsed) override;


	virtual void onLeaveChannel(const RtcStats& stats) override;


	virtual void onRejoinChannelSuccess(const char* channel, uid_t uid, int elapsed) override;


	virtual void onUserJoined(uid_t uid, int elapsed) override;


	virtual void onWarning(int warn, const char* msg) override;


	virtual void onUserOffline(uid_t uid, USER_OFFLINE_REASON_TYPE reason) override;


	virtual void onConnectionBanned() override;


	virtual void onConnectionInterrupted() override;


	virtual void onConnectionLost() override;


	virtual void onLastmileQuality(int quality) override;


	virtual void onNetworkQuality(uid_t uid, int txQuality, int rxQuality) override;


	virtual void onUserMuteAudio(uid_t uid, bool muted) override;

private:
	static UAgoraVoiceCallBack *AgoraVoiceCBInstance;
	TWeakObjectPtr<UAgoraVoiceManager> AgoraVoiceManager;
	
};
