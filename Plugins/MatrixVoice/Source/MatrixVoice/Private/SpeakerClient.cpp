// Fill out your copyright notice in the Description page of Project Settings.

#include "SpeakerClient.h"
#include "Notify.h"
#include "ScopeLock.h"
USpeakerClient* USpeakerClient::SpeakerClient = nullptr;
USpeakerClient::USpeakerClient(const FObjectInitializer &ObjectInitalizer)
{
	m_voiceengine = gcloud_voice::GetVoiceEngine();
}
USpeakerClient::~USpeakerClient()
{
}

int32 USpeakerClient::SetAppInfo(const FString appId, const FString appKey, const FString openId)
{
	int32 ErrorCode;
	if (m_voiceengine != nullptr)
	{
		return  static_cast<int32>(m_voiceengine->SetAppInfo(TCHAR_TO_ANSI(*appId), TCHAR_TO_ANSI(*appKey), TCHAR_TO_ANSI(*openId)));
		
	}
	ErrorCode = -1;
	return ErrorCode;
	/*FString test = "fsdfs";
	char tests = 'ss';
	std::string sst= TCHAR_TO_UTF8(*test);*/
}

int32 USpeakerClient::Init()
{
	int32 ErrorCode;
	if (m_voiceengine != nullptr)
	{
		ErrorCode = static_cast<int32>(m_voiceengine->Init());
		if (ErrorCode == 4098)
		{
			UE_LOG(LogTemp, Warning, TEXT("Need SetAppInfo Before"));
		}
		return ErrorCode;
	}
	ErrorCode = -1;
	return ErrorCode;
}

int32 USpeakerClient::SetVoiceMode(EVoiceMode Mode)
{
	int32 ErrorCode;
	if (m_voiceengine!=nullptr)
	{
	  ErrorCode= static_cast<int32>(m_voiceengine->SetMode(static_cast<gcloud_voice::IGCloudVoiceEngine::GCloudVoiceMode>(Mode)));
	  if (ErrorCode == 4098)
	  {
		  UE_LOG(LogTemp, Warning, TEXT("Need SetAppInfo Before"));
	  }
	  return ErrorCode;
	}
	ErrorCode = -1;
	return ErrorCode;
}

USpeakerClient * USpeakerClient::GetSpeakerClient()
{   FCriticalSection SynchronizationObject;
	if (SpeakerClient == nullptr)
	{
		FScopeLock Lock(&SynchronizationObject);
		if (SpeakerClient == nullptr)
		{
			SpeakerClient = NewObject<USpeakerClient>();
			SpeakerClient->AddToRoot();
		}
		
	}
	return SpeakerClient;
}

int32 USpeakerClient::JoinTeamRoom(const FString roomName, int32 TimeOut)
{
	int32 ErrorCode;
	if (m_voiceengine!=nullptr)
	{
		return static_cast<int32>(m_voiceengine->JoinTeamRoom(TCHAR_TO_ANSI(*roomName),TimeOut));
	 
	}
	
	ErrorCode = -1;
	return ErrorCode;
}

int32 USpeakerClient::JoinNationalRoom(const FString roomName, EVoiceMemberRole MeberRole, int32 TimeOut)
{
	int32 ErrorCode;
	if (m_voiceengine!=nullptr)
	{
		return static_cast<int32>(m_voiceengine->JoinNationalRoom(TCHAR_TO_ANSI(*roomName), static_cast<gcloud_voice::IGCloudVoiceEngine::GCloudVoiceMemberRole>(MeberRole), TimeOut));
	
	}
	ErrorCode = -1;
	return ErrorCode;
}


int32 USpeakerClient::QuitRoom(const FString roomName, int32 TimeOut)
{
	int32 ErrorCode;
	if (m_voiceengine!=nullptr)
	{  
		return static_cast<int32>(m_voiceengine->QuitRoom(TCHAR_TO_ANSI(*roomName), TimeOut)) ;
		
	}
	ErrorCode = -1;
	return ErrorCode;
}

int32 USpeakerClient::OpenMic()
{   
	int32 ErrorCode;
	if (m_voiceengine!=nullptr)
	{
		return  static_cast<int32>(m_voiceengine->OpenMic());
	
	}
	ErrorCode = -1;
	return ErrorCode;
}

int32 USpeakerClient::CloseMic()
{
	int32 ErrorCode;
	if (m_voiceengine!=nullptr)
	{
		return static_cast<int32>(m_voiceengine->CloseMic());
		
	}
	ErrorCode = -1;
	return ErrorCode;
}

int32 USpeakerClient::OpenSpeaker()
{
	int32 ErrorCode;
	if (m_voiceengine!=nullptr)
	{
		return static_cast<int32>(m_voiceengine->OpenSpeaker());
		
	}
	ErrorCode = -1;
	return ErrorCode;
}

int32 USpeakerClient::CloseSpeaker()
{
	int32 ErrorCode;
	if (m_voiceengine!=nullptr)
	{
		return static_cast<int32>(m_voiceengine->CloseSpeaker());
		
	}
	ErrorCode = -1;
	return ErrorCode;
}

int32 USpeakerClient::SetMicVolume(int vol)
{
	int32 ErrorCode;
	if (m_voiceengine!=nullptr)
	{
		return  static_cast<int32>(m_voiceengine->SetMicVolume(vol));
	
	}
	ErrorCode = -1;
	return ErrorCode;
}

int32 USpeakerClient::SetSpeakerVolume(int vol)
{
	int32 ErrorCode;
	if (m_voiceengine != nullptr)
	{
		return static_cast<int32>(m_voiceengine->SetSpeakerVolume(vol));
		
	}
	ErrorCode = -1;
	return ErrorCode;
}

int32 USpeakerClient::SetNotify(UNotify * Notify)
{
	int32 ErrorCode;
	if (m_voiceengine!=nullptr)
	{
		return static_cast<int32>(m_voiceengine->SetNotify(Notify));
	}
	ErrorCode = -1;
	return ErrorCode;
}

void USpeakerClient::AddJoinedRoomName(const FString RoomName)
{
	if (JoinedRoomName.Num()==0)
	{
		//OpenMic();
		OpenSpeaker();
		//SetMicVolume(100);
		SetSpeakerVolume(100);
		
	}
	if (!JoinedRoomName.Contains(RoomName))
	{
		JoinedRoomName.Add(RoomName);
	}
}

void USpeakerClient::RemoveJoinedRoomName(const FString RoomName)
{
	if (JoinedRoomName.Contains(RoomName))
	{
		JoinedRoomName.Remove(RoomName);
	}
	if (JoinedRoomName.Num()==0)
	{
		CloseMic();
		CloseSpeaker();
		JoinedRoomName.Empty();
	}
}

void USpeakerClient::Tick(float DeltaTime)
{
	int32 ErrorCode;
	if (m_voiceengine!=nullptr)
	{
	  ErrorCode=static_cast<int32>(m_voiceengine->Poll());
	 if (ErrorCode== 4105)
	{
		UE_LOG(LogTemp, Warning, TEXT("NOT INIT"));
	}
	}
}

bool USpeakerClient::IsTickable() const
{
	return true;
}

TStatId USpeakerClient::GetStatId() const
{
	return TStatId();
}
