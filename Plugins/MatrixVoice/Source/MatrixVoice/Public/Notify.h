// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GCloudVoice.h"
#include "TypeExtension.h"
#include "UObject/NoExportTypes.h"
#include "Notify.generated.h"
using namespace gcloud_voice;
/**
 * 
 */

UCLASS(BlueprintType)
class MATRIXVOICE_API UNotify : public UObject,public IGCloudVoiceNotify
{
	GENERATED_BODY()
public:
	UNotify(const FObjectInitializer& ObjectInitializer);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnJoinRoom, EGCloudVoiceCompleteCode, code, FString, roomName, int32, memberID);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnQuitRoom, EGCloudVoiceCompleteCode, code, FString, roomName);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnMemberVoice, FString, roomName, int32, member, int32, status);

public:
	// Real-Time Callback
	/**
	* Callback when JoinXxxRoom successful or failed.
	*
	* @param code : a GCloudVoiceCompleteCode code . You should check this first.
	* @param roomName : name of your joining, should be 0-9A-Za-Z._- and less than 127 bytes
	* @param memberID : if success, return the memberID
	*/
	virtual void OnJoinRoom(GCloudVoiceCompleteCode code, const char *roomName, int memberID) override;

	/**
	* Callback when dropped from the room
	*
	* @param code : a GCloudVoiceCompleteCode code . You should check this first.
	* @param roomName : name of your joining, should be 0-9A-Za-Z._- and less than 127 bytes
	* @param memberID : if success, return the memberID
	*/
	virtual void OnStatusUpdate(GCloudVoiceCompleteCode status, const char *roomName, int memberID)override;

	/**
	* Callback when QuitRoom successful or failed.
	*
	* @param code : a GCloudVoiceCompleteCode code . You should check this first.
	* @param roomName : name of your joining, should be 0-9A-Za-Z._- and less than 127 bytes
	*/
	virtual void OnQuitRoom(GCloudVoiceCompleteCode code, const char *roomName)override;

	/**
	** Deprecate from GVoice 1.1.14
	* Callback when someone saied or silence in the same room.
	*
	* @param count: count of members who's status has changed.
	* @param members: a int array composed of [memberid_0, status,memberid_1, status ... memberid_2*count, status]
	* here, status could be 0, 1, 2. 0 meets silence and 1/2 means saying
	*/
	virtual void OnMemberVoice(const unsigned int *members, int count)override;


	/**
	* Callback when someone saied or silence in the same room.
	*
	* @param roomName: name of the room.
	* @param member: the member's ID
	* @param status : status could be 0, 1, 2. 0 meets silence and 1/2 means saying
	*/
	virtual void OnMemberVoice(const char *roomName, unsigned int member, int status)override;

	// Voice Message Callback
	/**
	* Callback when upload voice file successful or failed.
	*
	* @param code: a GCloudVoiceCompleteCode code . You should check this first.
	* @param filePath: file to upload
	* @param fileID: if success ,get back the id for the file.
	*/
	virtual void OnUploadFile(GCloudVoiceCompleteCode code, const char *filePath, const char *fileID)override;

	/**
	* Callback when download voice file successful or failed.
	*
	* @param code: a GCloudVoiceCompleteCode code . You should check this first.
	* @param filePath: file to download to .
	* @param fileID: if success ,get back the id for the file.
	*/
	virtual void OnDownloadFile(GCloudVoiceCompleteCode code, const char *filePath, const char *fileID)override;

	/**
	* Callback when finish a voice file play end.
	*
	* @param code: a GCloudVoiceCompleteCode code . You should check this first.
	* @param filePath: file had been plaied.
	*/
	virtual void OnPlayRecordedFile(GCloudVoiceCompleteCode code, const char *filePath)override;

	/**
	* Callback when query message key successful or failed.
	*
	* @param code: a GCloudVoiceCompleteCode code . You should check this first.
	*/
	virtual void OnApplyMessageKey(GCloudVoiceCompleteCode code)override;

	// Translate
	/**
	* Callback when translate voice to text successful or failed.
	*
	* @param code: a GCloudVoiceCompleteCode code . You should check this first.
	* @param fileID : file to translate
	* @param result : the destination text of the destination language.
	*/
	virtual void OnSpeechToText(GCloudVoiceCompleteCode code, const char *fileID, const char *result)override;

	/**
	* Callback when client is using microphone recording audio
	*
	* @param pAudioData : audio data pointer
	* @param nDataLength : audio data length
	* @param result : void
	*/
	virtual void OnRecording(const unsigned char* pAudioData, unsigned int nDataLength)override;

	/**
	* Callback when translate voice to text successful or failed.
	*/
	virtual void OnStreamSpeechToText(GCloudVoiceCompleteCode code, int error, const char *result, const char *voicePath)override;

	/**
	* Callback when change to another role
	*/
	virtual void OnRoleChanged(GCloudVoiceCompleteCode code, const char *roomName, int memberID, int role)override;

	//Get NotifyInstance
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "MatriVoiceNotify")
	static UNotify *GetNotifyInstance();
	UFUNCTION(BlueprintCallable,BlueprintPure,Category="ReadJson")
	static FString GetOpenId(FString path);
	public:
		UPROPERTY(BlueprintAssignable, Category = "MatriVoiceNotify")
			FOnJoinRoom onJoinRoom;
		UPROPERTY(BlueprintAssignable, Category = "MatriVoiceNotify")
			FOnQuitRoom onQuitRoom;
		class USpeakerClient *SpeakerClient = nullptr;
		private:
			static UNotify *NotifyInstance;
	
};
