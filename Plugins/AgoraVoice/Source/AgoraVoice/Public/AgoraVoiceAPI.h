// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include  "AgoraVoiceExtension.h"
#include "IAgoraRtcEngine.h"
#include "AgoraVoiceAPI.generated.h"
using namespace agora;
using namespace rtc;
//using namespace signaling;
/**
 *
 */class UAgoraVoiceCallBack;
UCLASS(BlueprintType)
class AGORAVOICE_API UAgoraVoiceAPI : public UObject
{
	GENERATED_BODY()
public:
	UAgoraVoiceAPI(const FObjectInitializer &ObjectInitializer);
	void Login();

	int SetChanelProfile(ECHANNEL_PROFILE_TYPE ChannelProfile = ECHANNEL_PROFILE_TYPE::CHANNEL_PROFILE_COMMUNICATION);
	int EnableAudio();
	int DisableAudio();
	int SetAudioProfile(EAUDIO_PROFILE_TYPE	AudioProfile = EAUDIO_PROFILE_TYPE::AUDIO_PROFILE_DEFAULT, EAUDIO_SCENARIO_TYPE AudioScenario = EAUDIO_SCENARIO_TYPE::AUDIO_SCENARIO_DEFAULT);
	int JoinChannel(const FString &ChannelID, int32 uid = 0, const FString &Token = TEXT("null"));
	int LeaveChannel();
	int SetEffectVolume(int volume);
	void SaveLog(const FString &file);
	int MuteLocalAudioStream(bool mute);
	int MuteAllRemoteAudioStreams(bool mute);
	int MuteRemoteAudioStream(int32 uid, bool mute);
	void ReleaseRtcEgine();
	void SetPlayDeviceVolume(int volume);
	virtual int32 GetFunctionCallspace(UFunction* Function, void* Parameters, FFrame* Stack) override;

private:
	IRtcEngine *RtcEngineInstance = nullptr;
	//IRtcEngineParameter *RtcEngineParameter = nullptr;
	TSharedPtr<RtcEngineParameters> RtcEngineParameter;
	//agora::util::AutoPtr<IAudioDeviceManager> AudioDeviceManager;
	UAgoraVoiceCallBack *CallBackInstance;



};
