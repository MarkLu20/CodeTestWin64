// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TypeExtension.h"
#include "VoiceObject.generated.h"
class USpeakerClient;
class UNotify;
/**
 * 
 */
UCLASS()
class MATRIXVOICE_API UVoiceObject : public UObject
{
	GENERATED_BODY()

		UVoiceObject(const FObjectInitializer &ObjectInitizlizer);
	UFUNCTION()
		void OnJoinRoomCallBack(EGCloudVoiceCompleteCode code, FString RoomName, int32 MemberID);
	UFUNCTION()
		void QuitRoomCallBack(EGCloudVoiceCompleteCode code, FString RoomName);
	
	USpeakerClient * SpeakerClientInstance = nullptr;
	UNotify *NotifyInstance = nullptr;
public:
	void JoinRoom(FString RoomName,int32 TimeOut);
	void QuitRoom(FString RoomName, int32 TimeOut);
	int32 OpenMic(int Vol);
	int32 CloseMic();
	static UVoiceObject *VoiceObjectInstance ;
	static UVoiceObject *GetVoiceObjectInstance();
};
