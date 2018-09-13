// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AgoraVoiceManager.generated.h"
class UAgoraVoiceAPI;
class UAgoraVoiceCallBack;
/**
 * UAgoraVoiceAPI
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FJoinSuccessDel,const FString&,RoomName,int32,Uid);
UCLASS()
class AGORAVOICE_API UAgoraVoiceManager : public UObject
{
	GENERATED_BODY()
public:
	UAgoraVoiceManager(const FObjectInitializer &ObjectInitializer);
	~UAgoraVoiceManager();
	static UAgoraVoiceManager *GetVoiceManager();
	UFUNCTION(BlueprintCallable)
		void Login();
	UFUNCTION(BlueprintCallable)
		int JoinChannel(const FString &ChannelID, int32 uid = 0, const FString &Token = TEXT("null"));
	/*打开音频 默认是打开的*/
	UFUNCTION(BlueprintCallable, Category = "AgoraVoice")
		int EnableAudio();
	UFUNCTION(BlueprintCallable, Category = "AgoraVoice")
		int DisableAudio();
	UFUNCTION(BlueprintCallable, Category = "AgoraVoice")
		int MuteLocalAudioStream(bool mute);
	/*静音所有远端音频*/
	/*参数  描述
	mute  true 静音所有远端的用户  false 取消静音远端的所有的客户*/
	UFUNCTION(BlueprintCallable, Category = "AgoraVoice")
		int MuteAllRemoteAudioStreams(bool mute);
	/*静音指定用户音频
	参数  描述
	uid    指定用户 ID
	muted  true 停止接收和播放指定音频流 false 允许接收和播放指定音频流*/
	UFUNCTION(BlueprintCallable, Category = "AgoraVoice")
		int MuteRemoteAudioStream(int32 uid, bool mute);
		/** The MyProperty */
	UPROPERTY(BlueprintAssignable, Category = "AgoraVoice")
		FJoinSuccessDel JoinSuccessDel;
	UFUNCTION(BlueprintCallable, Category = "AgoraVoice")
		void SetPlayDeviceVolume(int volume);
	void ReleaseRtcEgine();
	UFUNCTION(BlueprintCallable, Category = "AgoraVoice")
	void LeaveChannel();
	TWeakObjectPtr< UAgoraVoiceAPI> API;
private:
	TWeakObjectPtr<UAgoraVoiceAPI> VoiceAPI;
	 
	UAgoraVoiceCallBack *VoiceCallBack;
	static UAgoraVoiceManager *VoiceManager;

};
