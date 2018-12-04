// Fill out your copyright notice in the Description page of Project Settings.

#include "Notify.h"
#include "SpeakerClient.h"
#include "Json.h"
#include "Paths.h"
#include "FileHelper.h"
#include "ScopeLock.h"
UNotify* UNotify::NotifyInstance = nullptr;
 UNotify::UNotify(const FObjectInitializer& ObjectInitializer)
{
	 SpeakerClient = USpeakerClient::GetSpeakerClient();


}

 void UNotify::OnJoinRoom(gcloud_voice::GCloudVoiceCompleteCode code, const char *roomName, int memberID)
{
	if (gcloud_voice::GV_ON_JOINROOM_SUCC==code)
	{
		SpeakerClient->AddJoinedRoomName(FString(ANSI_TO_TCHAR(roomName)));
	}
	else
	{
		SpeakerClient->RemoveJoinedRoomName(FString(ANSI_TO_TCHAR(roomName)));
	}
	onJoinRoom.Broadcast(static_cast<EGCloudVoiceCompleteCode>(code),FString(ANSI_TO_TCHAR(roomName)),memberID);
}
void UNotify::OnStatusUpdate(GCloudVoiceCompleteCode status, const char * roomName, int memberID)
{
}

void UNotify::OnQuitRoom(GCloudVoiceCompleteCode code, const char * roomName)
{   
	onQuitRoom.Broadcast(static_cast<EGCloudVoiceCompleteCode>(code), ANSI_TO_TCHAR(roomName));
}

void UNotify::OnMemberVoice(const unsigned int * members, int count)
{
}

void UNotify::OnMemberVoice(const char * roomName, unsigned int member, int status)
{
}

void UNotify::OnUploadFile(GCloudVoiceCompleteCode code, const char * filePath, const char * fileID)
{
}

void UNotify::OnDownloadFile(GCloudVoiceCompleteCode code, const char * filePath, const char * fileID)
{
}

void UNotify::OnPlayRecordedFile(GCloudVoiceCompleteCode code, const char * filePath)
{
}

void UNotify::OnApplyMessageKey(GCloudVoiceCompleteCode code)
{

}

void UNotify::OnSpeechToText(GCloudVoiceCompleteCode code, const char * fileID, const char * result)
{
}

void UNotify::OnRecording(const unsigned char * pAudioData, unsigned int nDataLength)
{
}

void UNotify::OnStreamSpeechToText(GCloudVoiceCompleteCode code, int error, const char * result, const char * voicePath)
{
}

void UNotify::OnRoleChanged(GCloudVoiceCompleteCode code, const char * roomName, int memberID, int role)
{
}

UNotify * UNotify::GetNotifyInstance()
{
	FCriticalSection SynchronizationObject;
	if (NotifyInstance==nullptr)
	{
		FScopeLock Lock(&SynchronizationObject);
		if (NotifyInstance==nullptr)
		{
			NotifyInstance = NewObject<UNotify>();
			NotifyInstance->AddToRoot();
		}
		
	}
	return NotifyInstance;
}

FString UNotify::GetOpenId(FString path)
{
	/*FString JsonValue;
	path = FPaths::ProjectDir() / *path;
	FFileHelper::LoadFileToString(JsonValue,*path);
	TSharedPtr<FJsonObject> JsonObject;
	TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(JsonValue);
	bool BFlag = FJsonSerializer::Deserialize(JsonReader,JsonObject);
	FString OpenId = JsonObject->GetStringField("ID");*/

	return FString("");
}
