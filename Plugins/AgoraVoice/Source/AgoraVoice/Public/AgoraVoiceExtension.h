// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine.h"

UENUM(BlueprintType)
enum class ECHANNEL_PROFILE_TYPE :uint8
{
	CHANNEL_PROFILE_COMMUNICATION = 0,
	CHANNEL_PROFILE_LIVE_BROADCASTING = 1,
	CHANNEL_PROFILE_GAME = 2,
};
UENUM(BlueprintType)
enum class EAUDIO_PROFILE_TYPE :uint8
{
	AUDIO_PROFILE_DEFAULT = 0, // use default settings
	AUDIO_PROFILE_SPEECH_STANDARD = 1, // 32Khz, 18kbps, mono, speech
	AUDIO_PROFILE_MUSIC_STANDARD = 2, // 48Khz, 50kbps, mono, music
	AUDIO_PROFILE_MUSIC_STANDARD_STEREO = 3, // 48Khz, 50kbps, stereo, music
	AUDIO_PROFILE_MUSIC_HIGH_QUALITY = 4, // 48Khz, 128kbps, mono, music
	AUDIO_PROFILE_MUSIC_HIGH_QUALITY_STEREO = 5, // 48Khz, 128kbps, stereo, music
	AUDIO_PROFILE_NUM = 6,
};
UENUM(BlueprintType)
enum class EAUDIO_SCENARIO_TYPE :uint8
{
	AUDIO_SCENARIO_DEFAULT = 0,
	AUDIO_SCENARIO_CHATROOM = 1,
	AUDIO_SCENARIO_EDUCATION = 2,
	AUDIO_SCENARIO_GAME_STREAMING = 3,
	AUDIO_SCENARIO_SHOWROOM = 4,
	AUDIO_SCENARIO_NUM = 5,
};

