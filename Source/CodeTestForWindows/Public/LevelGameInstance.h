// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine/GameEngine.h"
#include "EngineGlobals.h"
#include "SceneManagerActor.h"
#include "MXLoadingScreen/Public/MXLoadingScreen.h"
#include "Package.h"
#include "UnrealSignal.h"
#include "SqliteSupport.h"
#include "Runnable.h"
#include "Runtime/SlateCore/Public/Widgets/SWindow.h"
#include "AgoraVoiceTestActor.h"
#include "LevelGameInstance.generated.h"

/**
 * 
 */
class UOpenFireChatAPI;
UCLASS()
class CODETESTFORWINDOWS_API ULevelGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
		

		ULevelGameInstance(/*const FObjectInitializer &ObjectInializer*/);

		virtual void Init() override;


		virtual void Shutdown() override;


		virtual void LoadComplete(const float LoadTime, const FString& MapName) override;

public:
	FLoadPackageAsyncDelegate _tmpDelegate;
	

	void LoadingCallBack(const FName& _packageName, const TArray<FName>& _allLevelNames, const TArray<FName>& _loadedLevelNames, float _percent);
	UFUNCTION(BlueprintCallable)
	void OpenLevel();
	void LoadAsyncCB(const FName &Name,UPackage *Package,EAsyncLoadingResult::Type Result);
	void OnAssetLoadedFunc(UObject *LoadedObject);
	void LoadOver();
	void ReviceMapName(const FString &MapName);
	void EndMap(UWorld *World);
   UFUNCTION(BlueprintCallable)
	void ShowLoadingScreen();
   UFUNCTION(BlueprintCallable)
	   void HideLoadingScreen();
   void DirtyPackage(UPackage *Package);
   UFUNCTION(BlueprintCallable)
   void FindAllUStruct();
   UFUNCTION(BlueprintCallable)
	   void MixScreen();
	float	LastLoadIndex;
	float StreamingArrayNum;
	float loadtime = 0;
	TWeakObjectPtr< UOpenFireChatAPI> OpenFire;
		
		UFUNCTION(BlueprintCallable, Category = "OpenFire")
			void Login(FString ServerAddr, int32 ServerPort, bool bUseSSL, bool bUsePlainTextAuth, float PingInterval, float PingTimeOut, int32 MaxPingRetries, bool bPrivateChatFriendsOnly, const FString  &UserID, const FString &Auth);
		UFUNCTION(BlueprintCallable, Category = "OpenFire")
			void SendPrivateMessage(const FString &FromUser, const FString &ToUser, const FString &Msg);
		UFUNCTION(BlueprintCallable, Category = "OpenFire")
			void MucSendMessage(const FString& FromUser, const FString& Message, const FString &Type);
		UFUNCTION(BlueprintCallable, Category = "OpenFire")
			void JoinRoom(const FString &Room);
		UFUNCTION(BlueprintCallable, Category = "OpenFire")
			void InivteJoinRoom(const FString &FromUser,const FString &ToUser,const FString &RoomName );
		UFUNCTION(BlueprintCallable, Category = "OpenFire")
			void InviteJoinRoom(const FString &FromUser, const FString &ToUser, const FString &RoomName);
		void Test(int a, float b);
		UFUNCTION(BlueprintCallable)
			void  TestFunction();
		/** Does the thing. */
		UFUNCTION(BlueprintCallable, Category = "Game Play")
			void ExcuteExe(const FString &Path);

		template<typename T>
		void PassFunction(T *oject)
		{   
8			//testfuncPointer= [oject](int val, float valf) { oject->Test(val, valf); };
		
		};

private:
	TArray<class ULevelStreaming *> StreamingArray;
	int32 Index;
	bool HasLoaded(FName PackageName);
	TFunction<void(int,float)> testfuncPointer;
	void OnEndFrameDel();
	//TSharedPtr < SMXLoadingScreenWidget >LoadingScreenWidget;
private:
	UPROPERTY()
		TSubclassOf<UUserWidget> StartingWidgetClass;
	UPROPERTY()
		UUserWidget* CurrentWidget = nullptr;
	void OnRequestDestroyWindowOverride(const TSharedRef<SWindow>& SWindow);

	FRequestDestroyWindowOverride RequestDestroyWindowOverride;
	IMXLoadingScreenModule *LoadingScreenModule=nullptr;
};



