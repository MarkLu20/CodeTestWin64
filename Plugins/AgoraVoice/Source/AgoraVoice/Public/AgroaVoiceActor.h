// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AgroaVoiceActor.generated.h"
class UAgoraVoiceManager;
UCLASS()
class AGORAVOICE_API AAgroaVoiceActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AAgroaVoiceActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = AgoraTest)
		int SetChanelProfile(ECHANNEL_PROFILE_TYPE ChannelProfile = ECHANNEL_PROFILE_TYPE::CHANNEL_PROFILE_COMMUNICATION);
	UFUNCTION(BlueprintCallable, Category = AgoraTest)
		int EnableAudio();
	UFUNCTION(BlueprintCallable, Category = AgoraTest)
		int DisableAudio();
	UFUNCTION(BlueprintCallable, Category = AgoraTest)
		int SetAudioProfile(EAUDIO_PROFILE_TYPE	AudioProfile = EAUDIO_PROFILE_TYPE::AUDIO_PROFILE_DEFAULT, EAUDIO_SCENARIO_TYPE AudioScenario = EAUDIO_SCENARIO_TYPE::AUDIO_SCENARIO_DEFAULT);

	UFUNCTION(BlueprintCallable, Category = AgoraTest)
		int JoinChannel(const FString &ChannelID, int32 uid = 0, const FString &Token = TEXT("null"));
	/*离开房间*/
	UFUNCTION(BlueprintCallable, Category = AgoraTest)
		void LeaveChannel();
	UFUNCTION(BlueprintCallable, Category = AgoraTest)
		int SetEffectVolume(int volume);
	UFUNCTION(BlueprintCallable, Category = AgoraTest)
		void SetPlayDeviceVolume(int volume);
	void SaveLog(const FString &file);
	/*将自己静音 */
	/*参数  描述
	mute  bool类型 true麦克风静音 false 麦克风取消静音*/
	UFUNCTION(BlueprintCallable, Category = AgoraTest)
		int MuteLocalAudioStream(bool mute);

	/*静音所有远端音频*/
	/*参数  描述
	mute  true 静音所有远端的用户  false 取消静音远端的所有的客户*/
	UFUNCTION(BlueprintCallable, Category = AgoraTest)
		int MuteAllRemoteAudioStreams(bool mute);
	/*静音指定用户音频
	参数  描述
	uid    指定用户 ID
	muted  true 停止接收和播放指定音频流 false 允许接收和播放指定音频流*/
	UFUNCTION(BlueprintCallable, Category = AgoraTest)
		int MuteRemoteAudioStream(int32 uid, bool mute);
	/** Does the thing. */
	UFUNCTION()
		void JoinSuccesscn(const FString &room,int32 uid);


private:
	TWeakObjectPtr<UAgoraVoiceManager> AVAPIManager;

};
