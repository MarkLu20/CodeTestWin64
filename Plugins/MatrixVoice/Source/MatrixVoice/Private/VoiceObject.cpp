// Fill out your copyright notice in the Description page of Project Settings.

#include "VoiceObject.h"
#include "Notify.h"
#include "SpeakerClient.h"
#include "ScopeLock.h"


UVoiceObject *UVoiceObject::VoiceObjectInstance = nullptr;

UVoiceObject * UVoiceObject::GetVoiceObjectInstance()
{    
	FCriticalSection SynchronizationObject;
	if (VoiceObjectInstance == nullptr)
	{
		FScopeLock Lock(&SynchronizationObject);
		if (VoiceObjectInstance==nullptr)
		{
			VoiceObjectInstance = NewObject<UVoiceObject>();
			VoiceObjectInstance->AddToRoot();
		}
		
	}
	return VoiceObjectInstance;
}

UVoiceObject::UVoiceObject(const FObjectInitializer &ObjectInitizlizer)
{  
	SpeakerClientInstance = USpeakerClient::GetSpeakerClient();
	NotifyInstance = UNotify::GetNotifyInstance();
	FString PlayerId = UNotify::GetOpenId(FString(L"./OpenID/OpenID.json"));
	SpeakerClientInstance->SetAppInfo(FString(TEXT("1629949810")), FString(TEXT("4da322a5228b3129e5669299293ab8f3")), PlayerId);
	SpeakerClientInstance->Init();

	SpeakerClientInstance->SetNotify(NotifyInstance);
	SpeakerClientInstance->SetVoiceMode(EVoiceMode::RealTime);
	NotifyInstance->onJoinRoom.AddDynamic(this, &UVoiceObject::OnJoinRoomCallBack);
	NotifyInstance->onQuitRoom.AddDynamic(this, &UVoiceObject::QuitRoomCallBack);
}

void UVoiceObject::OnJoinRoomCallBack(EGCloudVoiceCompleteCode code, FString RoomName, int32 MemberID)
{
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, FString("Joion Main Successed"));
}

void UVoiceObject::QuitRoomCallBack(EGCloudVoiceCompleteCode code, FString RoomName)
{
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, FString("Quit Main Successed"));
}

void UVoiceObject::JoinRoom(FString RoomName, int32 TimeOut)
{
	SpeakerClientInstance->JoinTeamRoom(RoomName, TimeOut);
}

void UVoiceObject::QuitRoom(FString RoomName, int32 TimeOut)
{
	SpeakerClientInstance->QuitRoom(RoomName, TimeOut);
}

int32 UVoiceObject::OpenMic(int Vol)
{
	SpeakerClientInstance->OpenMic();
	SpeakerClientInstance->SetMicVolume(100);
	return 0;
}

int32 UVoiceObject::CloseMic()
{

	return SpeakerClientInstance->CloseMic();
}

