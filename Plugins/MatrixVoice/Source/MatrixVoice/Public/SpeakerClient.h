// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TypeExtension.h"
#include "Tickable.h"
#include "UObject/NoExportTypes.h"
#include "Engine.h"
#include "GCloudVoice.h"
#include "SpeakerClient.generated.h"
using namespace gcloud_voice;
/**
 *
 */
UCLASS()
class MATRIXVOICE_API USpeakerClient : public UObject, public FTickableGameObject
{
	GENERATED_BODY()
public:
	 
	USpeakerClient(const FObjectInitializer &ObjectInitalizer);
	~USpeakerClient();

	UFUNCTION(BlueprintCallable, Category = "MatrixVoice")
		int32 SetAppInfo(const FString appId, const FString appKey, const FString openId);
	UFUNCTION(BlueprintCallable, Category = "MatrixVoice")
		int32 Init();
	UFUNCTION(BlueprintCallable, Category = "MatrixVoice")
		int32 SetVoiceMode(EVoiceMode Mode);
	UFUNCTION(BlueprintCallable, Category = "MatirxVoice")
		static USpeakerClient* GetSpeakerClient();
	UFUNCTION(BlueprintCallable, Category = "MatrixVoice")
		int32 JoinTeamRoom(const FString roomName,int32 TimeOut);
	UFUNCTION(BlueprintCallable, Category = "MatrixVoice")
		int32 JoinNationalRoom(const FString roomName, EVoiceMemberRole MeberRole,int32 TimeOut);
	UFUNCTION(BlueprintCallable, Category = "MatrixVoice")
		int32 QuitRoom(const FString roomName,int32 TimeOut);
	//加入房间内后打开麦克风 实时语音模式  当前以听众身份加入的大房间，不能开麦关麦
	UFUNCTION(BlueprintCallable, Category = "MatrixVoice")
		int32 OpenMic();
	//关闭麦克风 实时语音下已加入房间  当前以听众身份加入的大房间，不能开麦关麦
	UFUNCTION(BlueprintCallable, Category = "MatrixVoice")
		int32 CloseMic();
	//在实时语音的模式下，加入房间成功后（包括小队语音和国战语音），需要打开扬声器才能从网络接收数据并播放
	UFUNCTION(BlueprintCallable, Category = "MatrixVoice")
		int32 OpenSpeaker();
	//在实时语音的模式下，加入房间成功后（包括小队语音和国战语音），当不需要从网络接收数据并播放时，可以调用关闭麦克风接口
	UFUNCTION(BlueprintCallable, Category = "MatrixVoice")
		int32 CloseSpeaker();
	//设置麦克风音量
	UFUNCTION(BlueprintCallable, Category = "MatrixVoice")
		int32 SetMicVolume(int vol);
	//设置扬声器音量
	UFUNCTION(BlueprintCallable, Category = "MatrixVoice")
		int32 SetSpeakerVolume(int vol);
	//设置回调类
	UFUNCTION(BlueprintCallable, Category = "MatrixVoice")
		int32  SetNotify(UNotify *Notify);
	//加入房间后初始化相关设置
	void AddJoinedRoomName(const FString RoomName);
	//退出房间做相关设置
	void RemoveJoinedRoomName(const FString RoomName);



		// 通过 FTickableGameObject 继承
	virtual void Tick(float DeltaTime) override;

	virtual bool IsTickable() const override;

	virtual TStatId GetStatId() const override;
private:
	gcloud_voice::IGCloudVoiceEngine  *m_voiceengine = nullptr;
	 static USpeakerClient *SpeakerClient;
	 bool bRoomStatus;
	 TArray<FString> JoinedRoomName;


	

};
