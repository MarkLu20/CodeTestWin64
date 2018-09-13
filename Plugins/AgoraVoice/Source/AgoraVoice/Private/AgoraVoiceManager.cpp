// Fill out your copyright notice in the Description page of Project Settings.
#include "AgoraVoiceManager.h"
#include "AgoraVoiceAPI.h"
#include "AgoraVoiceCallBack.h"



UAgoraVoiceManager *UAgoraVoiceManager::VoiceManager = nullptr;
UAgoraVoiceManager::UAgoraVoiceManager(const FObjectInitializer &ObjectInitializer)
{
	VoiceAPI = GetDefault<UAgoraVoiceAPI>();
	//VoiceAPI->AddToRoot();
}

UAgoraVoiceManager::~UAgoraVoiceManager()
{

}

UAgoraVoiceManager* UAgoraVoiceManager::GetVoiceManager()
{
	if (VoiceManager==nullptr)
	{
		VoiceManager = NewObject<UAgoraVoiceManager>();
		VoiceManager->AddToRoot();
	}
	return VoiceManager;
}

void UAgoraVoiceManager::Login()
{
	//VoiceAPI->CreateAgoraRtcEngine();
	VoiceAPI->Login();
	
	
}

int UAgoraVoiceManager::JoinChannel(const FString &ChannelID, int32 uid /*= 0*/, const FString &Token /*= TEXT("null")*/)
{
	return VoiceAPI->JoinChannel(ChannelID,uid,Token);
}

int UAgoraVoiceManager::EnableAudio()
{
	return VoiceAPI->EnableAudio();
}

int UAgoraVoiceManager::DisableAudio()
{
	return VoiceAPI->DisableAudio();
}

int UAgoraVoiceManager::MuteLocalAudioStream(bool mute)
{
	return VoiceAPI->MuteLocalAudioStream(mute);
}

int UAgoraVoiceManager::MuteAllRemoteAudioStreams(bool mute)
{
	return VoiceAPI->MuteAllRemoteAudioStreams(mute);
}

int UAgoraVoiceManager::MuteRemoteAudioStream(int32 uid, bool mute)
{
	return VoiceAPI->MuteRemoteAudioStream(uid,mute);
}

void UAgoraVoiceManager::SetPlayDeviceVolume(int volume)
{
	VoiceAPI->SetPlayDeviceVolume(volume);
}

void UAgoraVoiceManager::ReleaseRtcEgine()
{
	VoiceAPI->ReleaseRtcEgine();
}

void UAgoraVoiceManager::LeaveChannel()
{
	VoiceAPI->LeaveChannel();
}
