// Fill out your copyright notice in the Description page of Project Settings.

#include "AgroaVoiceActor.h"
#include "AgoraVoiceManager.h"

// Sets default values
AAgroaVoiceActor::AAgroaVoiceActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AVAPIManager = GetDefault<UAgoraVoiceManager>();

}

// Called when the game starts or when spawned
void AAgroaVoiceActor::BeginPlay()
{
	Super::BeginPlay();
	AVAPIManager->Login();
	AVAPIManager->JoinSuccessDel.AddDynamic(this,&AAgroaVoiceActor::JoinSuccesscn);
	
	
}

// Called every frame
void AAgroaVoiceActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

int AAgroaVoiceActor::SetChanelProfile(ECHANNEL_PROFILE_TYPE ChannelProfile /*= ECHANNEL_PROFILE_TYPE::CHANNEL_PROFILE_COMMUNICATION*/)
{
	return 0;
}

int AAgroaVoiceActor::EnableAudio()
{
	return 0;
}

int AAgroaVoiceActor::DisableAudio()
{
	return 0;
}

int AAgroaVoiceActor::SetAudioProfile(EAUDIO_PROFILE_TYPE AudioProfile /*= EAUDIO_PROFILE_TYPE::AUDIO_PROFILE_DEFAULT*/, EAUDIO_SCENARIO_TYPE AudioScenario /*= EAUDIO_SCENARIO_TYPE::AUDIO_SCENARIO_DEFAULT*/)
{
	return 0;
}

int AAgroaVoiceActor::JoinChannel(const FString &ChannelID, int32 uid /*= 0*/, const FString &Token /*= TEXT("null")*/)
{
	return AVAPIManager->JoinChannel(ChannelID,uid);
}

void  AAgroaVoiceActor::LeaveChannel()
{
	 AVAPIManager->LeaveChannel();
}

int AAgroaVoiceActor::SetEffectVolume(int volume)
{
	return 0; //AVAPIManager->SetEffectVolume(volume);
}

void AAgroaVoiceActor::SetPlayDeviceVolume(int volume)
{
	AVAPIManager->SetPlayDeviceVolume(volume);
}

int AAgroaVoiceActor::MuteLocalAudioStream(bool mute)
{
	return AVAPIManager->MuteLocalAudioStream(mute);
}

int AAgroaVoiceActor::MuteAllRemoteAudioStreams(bool mute)
{
	return AVAPIManager->MuteAllRemoteAudioStreams(mute);
}

int AAgroaVoiceActor::MuteRemoteAudioStream(int32 uid, bool mute)
{
	return AVAPIManager->MuteRemoteAudioStream(uid,mute);
}

void AAgroaVoiceActor::JoinSuccesscn(const FString &room, int32 uid)
{
	UE_LOG(LogTemp,Error,TEXT("room %s uid %d"),*room,uid);
}

