// Fill out your copyright notice in the Description page of Project Settings.

#include "AgoraVoiceTestActor.h"
#include "AgoraVoiceManager.h"
#include "WebSocketTest.h"
#include "YanzhengObject.h"
#include "ModuleManager.h"
#include "WebSocketsModule.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "SingleTon.h"

// Sets default values
AAgoraVoiceTestActor::AAgoraVoiceTestActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;



}

// Called when the game starts or when spawned
void AAgoraVoiceTestActor::BeginPlay()
{
	UYanzhengObject *p = NewObject<UYanzhengObject>();
	Super::BeginPlay();

	
	//FSHA256Signature out;
	//bool test =this->SHA256(FString("fsadfsdfasdfasdf"), out);
	//UE_LOG(LogTemp,Error,TEXT("%fdsafsadf"))
	/*if (AvManager != nullptr)
	{
		AvManager->ReleaseRtcEgine();

	}*/
	//AvManager = UAgoraVoiceManager::GetVoiceManager();
	//AvManager->API.Get()->JoinChannel(FString("TestRoomfdsfd"));

	//Mangager = GetDefault<UAgoraVoiceManager>();

	//TArray<UObject *> ReferenceObejct;
	//FReferenceFinder ObjectReferenceCollector(ReferenceObejct, AvManager,false,true,true,false);
	//ObjectReferenceCollector.FindReferences(AvManager);
	//TSharedPtr


	//Mangager->Login(FString("fb50b66cf43940679083c25b520192b0"));
	/*int code = Mangager->JoinChannel(FString("TestRoomfdsfd"));
	int code1 = code;*/

}

// Called every frame
void AAgoraVoiceTestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAgoraVoiceTestActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	//AvManager->ReleaseRtcEgine();
	if (EndPlayReason == EEndPlayReason::EndPlayInEditor || EndPlayReason == EEndPlayReason::Quit)
	{

		TArray<FString> TestWebStr;

		TestWebStr.Add(TEXT("v10.stomp"));

		TestWebStr.Add(TEXT("v11.stomp"));

		FString url = FString(TEXT("ws://192.168.2.13:8081/websocket"));
		//testWeb->Closeoncet(url, TestWebStr);
		FString testetas;
		float a = 100.f;
		//Mangager->ReleaseRtcEgine();
		//Mangager->LeaveChannel();


	}
}

void AAgoraVoiceTestActor::DoThing()
{
	testWeb = GetDefault<UWebSocketTest>();
	TArray<FString> TestWebStr;
	//TestWebStr.Add(TEXT("ws"));
	//TestWebStr.Add(TEXT("wss"));
	//TestWebStr.Add(TEXT("v10.stomp"));
	//TestWebStr.Add(TEXT("v11.stomp"));
	TestWebStr.Add("Protocol");
	TestWebStr.Add("Protocol-v2");
	//testWeb->CreateWebScoket(FString("wss://echo.websocket.org"),TestWebStr);
	FString url = FString(TEXT("ws://192.168.2.13:8081/websocket"));
	//testWeb->Closeoncet(url,TestWebStr);
	
		testWeb->CreateWebScoket(url, TestWebStr);
		 UWorld *World= UGameplayStatics::GetPlayerController(this, 0)->GetWorld();
		 //UGameplayStatics::GetPlayerController(this, 0)->GetGameInstance()->
		 ULevel* Level = GetLevel();
		//ULevelScriptBlueprint *Bp= Level->GetLevelScriptBlueprint();
		//Bp->
		TestWebStr.Add("Protocol-v2");
		FString trestt="fsadfew";
	

}

void AAgoraVoiceTestActor::CacheString(const FString &Content)
{
	TWeakObjectPtr<USingleTon>	SingleTon = GetDefault<USingleTon>();
	SingleTon->CacheString(Content);
}

const TArray<FString>& AAgoraVoiceTestActor::GetCacheString()
{
	TWeakObjectPtr<USingleTon>	SingleTon = GetDefault<USingleTon>();
	return SingleTon->GetCacheString();
}

bool AAgoraVoiceTestActor::SHA256(const FString & data, FSHA256Signature & Out)
{
	return FGenericPlatformMisc::GetSHA256Signature(*data, static_cast<uint32>(data.GetAllocatedSize()), Out);
}

void GTC(FString fasdfasdf)
{
}
