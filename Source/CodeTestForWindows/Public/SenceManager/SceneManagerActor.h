// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SceneManagerActor.generated.h"


class UPackage;
class ULevelGameInstance;
DECLARE_MULTICAST_DELEGATE_FourParams(FAsyncLoadingLevelDelegate, const FName&, const TArray<FName>&, const TArray < FName>&, float);

UCLASS()
class CODETESTFORWINDOWS_API ASceneManagerActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASceneManagerActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	UFUNCTION(BlueprintCallable)
		static ASceneManagerActor* GetSceneMangerInStance();
	bool Openlevel(UWorld *World, const TCHAR *OpenLevelName);
	void  InitSceneM(ULevelGameInstance *Instance);
	//test

	void TestJoySceneManager(UWorld *World);
	void AsytncLoadPackage(const TCHAR * LoadPackageName, FAsyncLoadingLevelDelegate _delegate);
	void CallbackTimer();
	ULevelGameInstance *GetGameInstance()
	{
		return STGameInstance;
	}
	FName GetCurrentLoadPackage()
	{

		return _currentLoadPackage;
	}
	void TriggerLoadingDelegateCallBack(const FName& _packageName, const TArray<FName>& _allLevelNames, const TArray < FName>& _loadedLevelNames, float _percent);
	UFUNCTION(BlueprintCallable)
		void TestFString(const FString &test);
private:
	FAsyncLoadingLevelDelegate _loadingLevelDelegate;
	ULevelGameInstance *STGameInstance = nullptr;
	static ASceneManagerActor *SceneManagerInstance;
	FName _currentLoadPackage;
	bool IsLoading;
	bool loadPackage(const TCHAR *InLongPackagerName, uint32 LoadFlags);

	void Event_PreLoadMap(const FString &Unused);
	void Event_PostLoadMap();
	void Event_PackageAsync(const FName &PackageName, UPackage *Package, EAsyncLoadingResult::Type result, bool bAddToRoot);
	void Event_LevelRemoveFromWorld(ULevel *Level, UWorld *World);
	void Event_LevelAddedToWorld(ULevel *Level, UWorld *World);

	void RegisterLoadEvent();
};
class FJoyCheckPropressThread : public FRunnable
{
	static FJoyCheckPropressThread *_Runnable;
	FRunnableThread *_Thread;
	FThreadSafeCounter _stopTaskCounter;
private:
	ULevelGameInstance *cpt_gameInstance;
	TArray<FName> _loadLevels;
	TArray<FName> _loadedLevels;
	ASceneManagerActor *_SceneManger;
	FName _curLoadLevelName;
	float _curLoadingPercent;
	void CheckProperss();
	bool IsFinishedLoad();
	bool LoadingDone();
	TArray<FName> _levelString;

public:
	FJoyCheckPropressThread(TArray<FName> LevelNames, ASceneManagerActor *SceneManager);
	virtual ~FJoyCheckPropressThread();




private:
	// Í¨¹ý FRunnable ¼Ì³Ð
	virtual uint32 Run() override;


	virtual bool Init() override;


	virtual void Stop() override;


	virtual void Exit() override;
	void EnSureCompletion();
public:
	static void ShutDown();
	static FJoyCheckPropressThread *JoyInitAsyncCheck(TArray<FName> LevelNames, ASceneManagerActor *SceneManager);
	static bool IsThreadFinished();

};
