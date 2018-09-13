// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#ifndef  _TIMELINE_H_
#define  _TIMELINE_H_
#include "Runtime/Engine/Classes/Components/TimelineComponent.h"
#include "Tickable.h"
#include "Runtime/Engine/Classes/Curves/CurveFloat.h"
#endif// !_TIMELINE_H_
#include "TimeLineObject.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class ETimeLineType : uint8
{
   Throttle,
   Roll,
   Pitch,
   Yaw,
   Slow,
};
UCLASS(BlueprintType)
class CODETESTFORWINDOWS_API UTimeLineObject : public UObject ,public FTickableGameObject
{
	GENERATED_BODY()
public:
	UTimeLineObject(const FObjectInitializer &ObjectInitializer);
	

public:


	UCurveFloat *ThrottleimeLineCurve = nullptr;
	UCurveFloat *RollTimeLineCurve = nullptr;
	UCurveFloat *PitchTimeLineCurve = nullptr;
	UCurveFloat *YawTimeLineCurve = nullptr;
	UCurveFloat *SlowLineCurve = nullptr;

	FOnTimelineFloat ThrottleInterpFloat;
	FOnTimelineFloat RollInterpFloat;
	FOnTimelineFloat PitchInterpFloat;
	FOnTimelineFloat YawInterpFloat;
	FOnTimelineFloat SlowInerpFloat;

	FKeyHandle ThrottleLastHandle;
	FKeyHandle RollLastHandle;
	FKeyHandle PitchLastHandle;
	FKeyHandle YawLastHandle;
	FKeyHandle  SlowFirstHandle;
	FKeyHandle SlowLastHandle;

public:

	FTimeline ThrottleTimeLine;
	FTimeline RollTimeLine;
	FTimeline PitchTimeLine;
	FTimeline YawTimeLine;
	FTimeline SlowTimeLine;
	float Thrvalue;
	float SlowValue;
	float Rvalue;
	float Pvalue;
	float Yvalue;
	
	
	UFUNCTION()
		void GetThrottleTLValue(float Value);
	UFUNCTION()
		void GetRollTLValue(float Value);
	UFUNCTION()
		void GetPitchTLValue(float Value);
	UFUNCTION()
		void GetYawTLValue(float Value);
	UFUNCTION()
		void GetSlowValue(float Value);
	UFUNCTION(BlueprintCallable,Category = "Instance")
	static UTimeLineObject *GetTimeLineInstance();
	UFUNCTION(BlueprintCallable)
	void PlayTimeLine(ETimeLineType TimeLineType);
	UFUNCTION(BlueprintCallable)
	void StopTimeLine(ETimeLineType TimeLineType);
	// Í¨¹ý FTickableGameObject ¼Ì³Ð

	virtual void Tick(float DeltaTime) override;

	virtual bool IsTickable() const override;

	virtual TStatId GetStatId() const override;

private:
	static UTimeLineObject *TimeLineInstance;
	TMap<ETimeLineType, FTimeline> TimeLineMap;
	TMap<ETimeLineType, UCurveFloat *> CurveMap;
	TMap<ETimeLineType, FKeyHandle> KeyHandleMap;
	
	
};
