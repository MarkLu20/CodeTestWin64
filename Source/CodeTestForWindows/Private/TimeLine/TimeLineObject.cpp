// Fill out your copyright notice in the Description page of Project Settings.

#include "TimeLineObject.h"
#include "Engine.h"
UTimeLineObject *UTimeLineObject::TimeLineInstance = nullptr;
UTimeLineObject::UTimeLineObject(const FObjectInitializer &ObjectInitializer) : UObject(ObjectInitializer)
{

	ThrottleimeLineCurve = NewObject<UCurveFloat>();
	ThrottleimeLineCurve->AddToRoot();
	ThrottleimeLineCurve->FloatCurve.AddKey(0.0f,0.0f);
	ThrottleLastHandle = ThrottleimeLineCurve->FloatCurve.AddKey(10.0f,1.0f);
	ThrottleInterpFloat.BindDynamic(this, &UTimeLineObject::GetThrottleTLValue);
	ThrottleTimeLine.AddInterpFloat(ThrottleimeLineCurve,ThrottleInterpFloat,FName("ThrottleTimeLine"));
	
	TimeLineMap.Add(ETimeLineType::Throttle,ThrottleTimeLine);
	CurveMap.Add(ETimeLineType::Throttle,ThrottleimeLineCurve);
	KeyHandleMap.Add(ETimeLineType::Throttle,ThrottleLastHandle);

	RollTimeLineCurve = NewObject<UCurveFloat>();
	RollTimeLineCurve->AddToRoot();
	RollTimeLineCurve->FloatCurve.AddKey(0.0f,0.0f);
	RollLastHandle = RollTimeLineCurve->FloatCurve.AddKey(10.0f,1.0f);
	RollInterpFloat.BindDynamic(this,&UTimeLineObject::GetRollTLValue);
	RollTimeLine.AddInterpFloat(RollTimeLineCurve,RollInterpFloat,FName("RollTimeLine"));
	
	TimeLineMap.Add(ETimeLineType::Roll,RollTimeLine);
	CurveMap.Add(ETimeLineType::Roll,RollTimeLineCurve);
	KeyHandleMap.Add(ETimeLineType::Roll,RollLastHandle);
	TimeLineInstance->GetClass();
	  GetDefault<UTimeLineObject>();

}


void UTimeLineObject::GetThrottleTLValue(float Value)
{
	float Throttle;
	Throttle = FMath::Lerp(0.0f,10.0f,ThrottleimeLineCurve->GetFloatValue(Value));
	GEngine->AddOnScreenDebugMessage(-1,0.0f,FColor::Blue,FString(FString::SanitizeFloat(Throttle)));
	
}

void UTimeLineObject::GetRollTLValue(float Value)
{
	float Roll;
	Roll = FMath::Lerp(0.0f, 10.0f, ThrottleimeLineCurve->GetFloatValue(Value));
	GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Blue, FString(FString::SanitizeFloat(Roll)));
}

void UTimeLineObject::GetPitchTLValue(float Value)
{
}

void UTimeLineObject::GetYawTLValue(float Value)
{
}

void UTimeLineObject::GetSlowValue(float Value)
{
}

UTimeLineObject * UTimeLineObject::GetTimeLineInstance()
{
	if (TimeLineInstance==nullptr)
	{
		TimeLineInstance = NewObject<UTimeLineObject>();
		TimeLineInstance->AddToRoot();
	}
	return TimeLineInstance;
}

void UTimeLineObject::PlayTimeLine(ETimeLineType TimeLineType)
{
	if (TimeLineMap.Find(TimeLineType))
	{
		 (*TimeLineMap.Find(TimeLineType)).Play();
	}
	
	/*if (TimeLineType==ETimeLineType::Throttle)
	{
		ThrottleTimeLine.Play();
	}
	if (TimeLineType == ETimeLineType::Roll)
	{
		RollTimeLine.Play();
	}*/
}

void UTimeLineObject::StopTimeLine(ETimeLineType TimeLineType)
{
	/*if (TimeLineType == ETimeLineType::Throttle)
	{
		ThrottleTimeLine.SetNewTime(0.0f);
		ThrottleTimeLine.Stop();
	}*/

	(*TimeLineMap.Find(TimeLineType)).SetNewTime(0.0f);
	(*TimeLineMap.Find(TimeLineType)).Stop();
}

void UTimeLineObject::Tick(float DeltaTime)
{
	ThrottleTimeLine.TickTimeline(DeltaTime);
	RollTimeLine.TickTimeline(DeltaTime);
	(*TimeLineMap.Find(ETimeLineType::Throttle)).TickTimeline(DeltaTime);
	(*TimeLineMap.Find(ETimeLineType::Roll)).TickTimeline(DeltaTime);
}

bool UTimeLineObject::IsTickable() const
{
	return true;
}

TStatId UTimeLineObject::GetStatId() const
{
	return GetStatID();
}
