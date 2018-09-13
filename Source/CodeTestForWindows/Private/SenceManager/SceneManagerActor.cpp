// Fill out your copyright notice in the Description page of Project Settings.

#include "SceneManagerActor.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Engine/LevelStreaming.h"
#include "Engine.h"
#include "LevelGameInstance.h"
ASceneManagerActor *ASceneManagerActor::SceneManagerInstance = nullptr;
// Sets default values
ASceneManagerActor::ASceneManagerActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASceneManagerActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASceneManagerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

ASceneManagerActor * ASceneManagerActor::GetSceneMangerInStance()
{

	if (SceneManagerInstance == nullptr)
	{
		SceneManagerInstance = NewObject<ASceneManagerActor>();
		SceneManagerInstance->RegisterLoadEvent();

		SceneManagerInstance->AddToRoot();

	}
	return 	SceneManagerInstance;
}

bool ASceneManagerActor::Openlevel(UWorld * World, const TCHAR * OpenLevelName)
{
	ULevelGameInstance *Instance = nullptr;
	//Instance = Cast<ULevelGameInstance>(UGameplayStatics::GetGameInstance(this));
	Instance = GetGameInstance();
	FWorldContext *WorldContext = Instance->GetWorldContext();
	FURL testURL(&(WorldContext->LastURL), OpenLevelName, ETravelType::TRAVEL_Absolute);
	return false;
}

void ASceneManagerActor::InitSceneM(ULevelGameInstance * Instance)
{
	STGameInstance = Instance;
	IsLoading = false;
	UE_LOG(LogTemp, Error, TEXT("__________init scene Manager"));
}



void ASceneManagerActor::TestJoySceneManager(UWorld * World)
{
	UPackage* worldPackage = NULL;
	FString _URLName = L"/Game/Maps/BirthplaceMage";

	int32 rtnV = 0;
	rtnV = LoadPackageAsync(*_URLName, FLoadPackageAsyncDelegate::CreateUObject(this, &ASceneManagerActor::Event_PackageAsync, true));
	if (true || rtnV)
	{
		FlushAsyncLoading(rtnV);

		float loadPercentage = GetAsyncLoadPercentage(*_URLName);
		UE_LOG(LogTemp, Error, TEXT("---load percentgage = %f"), loadPercentage);
		int32 packNum = GetNumAsyncPackages();
		UE_LOG(LogTemp, Error, TEXT("---Num Async = %d"), packNum);
	}
}

void ASceneManagerActor::AsytncLoadPackage(const TCHAR * LoadPackageName, FAsyncLoadingLevelDelegate _delegate)
{
	if (!STGameInstance)
	{
		UE_LOG(LogTemp, Error, TEXT("WARNING: Joy Scene manager instance need init first!"));
		return;
	}

	_loadingLevelDelegate = _delegate;

	UWorld* world = STGameInstance->GetWorld();
	FWorldContext* worldContext = STGameInstance->GetWorldContext();

	FURL testURL(&worldContext->LastURL, LoadPackageName, TRAVEL_Absolute);
	if (testURL.IsLocalInternal())
	{
		if (!GEngine->MakeSureMapNameIsValid(testURL.Map))
		{
			UE_LOG(LogTemp, Error, TEXT("WARNING : the map '%s' does not exist!"), *testURL.Map);
			return;
		}
	}

	int32 packageHandle = LoadPackageAsync(*testURL.Map, FLoadPackageAsyncDelegate::CreateUObject(this, &ASceneManagerActor::Event_PackageAsync, true));
	if (packageHandle)
	{
		FlushAsyncLoading(packageHandle);
	}

	_currentLoadPackage = FName(*testURL.Map);
}

void ASceneManagerActor::CallbackTimer()
{
	GEngine->AddOnScreenDebugMessage(-1, 0.5, FColor::Blue, FString("call back timer"));

	FString _URLName = L"/Game/Maps/ThirdPersonExampleMap";
	float loadPercentage = GetAsyncLoadPercentage(*_URLName);

	if (loadPercentage != -1)
	{
		UE_LOG(LogTemp, Error, TEXT("---------------------------load percentgage = %f"), loadPercentage);
	}
}



void ASceneManagerActor::TriggerLoadingDelegateCallBack(const FName & _packageName, const TArray<FName>& _allLevelNames, const TArray<FName>& _loadedLevelNames, float _percent)
{
	_loadingLevelDelegate.Broadcast(_packageName, _allLevelNames, _loadedLevelNames, _percent);
	UE_LOG(LogTemp, Error, TEXT("----1-------"));
	if (_allLevelNames.Num() == _loadedLevelNames.Num())
	{
		//FJoyCheckProgressThread::Shutdown();
		UE_LOG(LogTemp, Error, TEXT("----234-------"));
	}
}

void ASceneManagerActor::TestFString(const FString & test)
{
	UE_LOG(LogTemp, Error, TEXT("%s"), *test);
}

bool ASceneManagerActor::loadPackage(const TCHAR * InLongPackagerName, uint32 LoadFlags)
{
	UPackage   *WorldPackage = nullptr;
	UWorld *NewWorld = nullptr;
	WorldPackage = FindPackage(nullptr, InLongPackagerName);
	if (WorldPackage == nullptr)
	{
		WorldPackage = LoadPackage(nullptr, InLongPackagerName, LoadFlags);
	}
	const FName URLMapName = FName(InLongPackagerName);
	NewWorld = UWorld::FindWorldInPackage(WorldPackage);
	if (NewWorld == nullptr)
	{
		return false;
	}
	return true;
}

void ASceneManagerActor::Event_PreLoadMap(const FString & Unused)
{
	IsLoading = true;
}

void ASceneManagerActor::Event_PostLoadMap()
{
	IsLoading = false;
	UE_LOG(LogTemp, Error, TEXT("PostLoadMap Event"));
}

void ASceneManagerActor::Event_PackageAsync(const FName & PackageName, UPackage * Package, EAsyncLoadingResult::Type result, bool bAddToRoot)
{
	float a=Package->GetLoadTime();
	FString pnStr = PackageName.ToString();
	UE_LOG(LogTemp, Error, TEXT("-----package async --- package name = %s"), *pnStr);
	UE_LOG(LogTemp, Error, TEXT("-----package async ---result type = %d"), *Package->GetName());
	UE_LOG(LogTemp, Error, TEXT("-----package async ---badd to root = %d"), bAddToRoot);

	if (result == EAsyncLoadingResult::Failed)
	{
		UE_LOG(LogTemp, Error, TEXT("WARNING: async loading '%s' package failed!"), *PackageName.ToString());
		return;
	}
	else if (result == EAsyncLoadingResult::Canceled)
	{
		UE_LOG(LogTemp, Error, TEXT("WARNING: async loading '%s' package Canceled!"), *PackageName.ToString());

		return;
	}
	else if (result == EAsyncLoadingResult::Succeeded)
	{
		UE_LOG(LogTemp, Error, TEXT("async loading '%s' package succeeded!"), *PackageName.ToString());
	}
	if (STGameInstance)
	{
		UWorld *CurrentWorld = STGameInstance->GetWorld();
		if (CurrentWorld)
		{

		}
		UWorld *PreWorld = UWorld::FindWorldInPackage(Package);
		if (PreWorld)
		{
			TArray<FName>_LevelNames;
			TArray<ULevelStreaming *> _streaminglevels = PreWorld->StreamingLevels;
			if (_streaminglevels.Num() > 0)
			{
				for (int32 i = 0; i < _streaminglevels.Num(); ++i)
				{
					ULevelStreaming *streamingLevel = _streaminglevels[i];
					FName _name = streamingLevel->GetWorldAssetPackageFName();
					_LevelNames.Push(_name);
				}
			}

			bool _hadLoaded = false;
			FWorldContext *WorldContext = STGameInstance->GetWorldContext();
			if (WorldContext && _LevelNames.Num() == WorldContext->LoadedLevelsForPendingMapChange.Num())
			{
				_hadLoaded = true;
				TriggerLoadingDelegateCallBack(_currentLoadPackage, _LevelNames, _LevelNames, 100);
			}
			if (_hadLoaded)
			{
				return;
			}
			if (_LevelNames.Num() > 0)
			{
				CurrentWorld->CancelPendingMapChange();
				CurrentWorld->PrepareMapChange(_LevelNames);
				FJoyCheckPropressThread::JoyInitAsyncCheck(_LevelNames, this);
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("does not exit levels need to load!"));
			}
		}
	}
}

void ASceneManagerActor::Event_LevelRemoveFromWorld(ULevel * Level, UWorld * World)
{
	UE_LOG(LogTemp, Error, TEXT("----- event level removed from world"));
}

void ASceneManagerActor::Event_LevelAddedToWorld(ULevel * Level, UWorld * World)
{
	UE_LOG(LogTemp, Error, TEXT("---- event level added to world"));
}

void ASceneManagerActor::RegisterLoadEvent()
{
	//FCoreUObjectDelegates::PostLoadMap.AddUObject(this, &ASceneManagerActor::Event_PostLoadMap);
	//FCoreUObjectDelegates::PreLoadMap.AddUObject(this, &ASceneManagerActor::Event_PreLoadMap);
	FWorldDelegates::LevelRemovedFromWorld.AddUObject(this, &ASceneManagerActor::Event_LevelRemoveFromWorld);
	FWorldDelegates::LevelAddedToWorld.AddUObject(this, &ASceneManagerActor::Event_LevelAddedToWorld);
}

FJoyCheckPropressThread *FJoyCheckPropressThread::_Runnable = nullptr;
FJoyCheckPropressThread::FJoyCheckPropressThread(TArray<FName> LevelNames, ASceneManagerActor * SceneManager)
	:_loadLevels(LevelNames)
	, _stopTaskCounter(0)
	, _loadedLevels()
	, _SceneManger(_SceneManger)
{
	cpt_gameInstance = _SceneManger->GetGameInstance();

	_Thread = FRunnableThread::Create(this, TEXT("FJoyMultiThreadWorkder"), 0, TPri_Normal);
}

void FJoyCheckPropressThread::CheckProperss()
{
	const FName _packageName = _SceneManger->GetCurrentLoadPackage();
	const TArray<FName> _LevelNames = _loadLevels;
	const TArray<FName> _loadedLevelNames = _loadedLevels;
	float _percent = _curLoadingPercent;
	if (_SceneManger)
	{
		_SceneManger->TriggerLoadingDelegateCallBack(_packageName, _LevelNames, _loadedLevelNames, _curLoadingPercent);
	}
}

bool FJoyCheckPropressThread::IsFinishedLoad()
{
	int32 tmpLevelNums = 0;
	if (_loadLevels.Num() > 0)
	{
		for (int32 i = 0; i < _loadLevels.Num(); ++i)
		{
			FName _levelName = _loadLevels[i];
			float LoadPercentage = GetAsyncLoadPercentage(_levelName);
			if (LoadPercentage != -1)
			{
				FString _levelStr = _levelName.ToString();
				if (LoadPercentage != 0)
				{
					_curLoadLevelName = FName(*_levelStr);
					_curLoadingPercent = LoadPercentage;
				}
			}
		}
	}
	if (cpt_gameInstance)
	{
		FWorldContext *WorldContext = cpt_gameInstance->GetWorldContext();
		if (WorldContext &&WorldContext->LoadedLevelsForPendingMapChange.Num() > 0)
		{
			_loadedLevels.Empty();
			TArray<ULevel *> _tempLeves = WorldContext->LoadedLevelsForPendingMapChange;
			for (auto _level : _tempLeves)
			{
				ULevel *_rlevel = Cast<ULevel>(_level);
				FString _name = _rlevel->OwningWorld->GetMapName();
				_loadedLevels.Push(FName(*_name));
			}
			UE_LOG(LogTemp, Error, TEXT("-------------Finished load Level = %d"), _tempLeves.Num());
			tmpLevelNums = _tempLeves.Num();
		}
	}
	CheckProperss();
	if (tmpLevelNums >= _loadLevels.Num())
	{
		return true;
	}
	return false;
}

bool FJoyCheckPropressThread::LoadingDone()
{

	FWorldContext *WorldContext = cpt_gameInstance->GetWorldContext();
	if (WorldContext && _loadLevels.Num() == WorldContext->LoadedLevelsForPendingMapChange.Num())
	{
		return true;
	}
	return false;

}


FJoyCheckPropressThread::~FJoyCheckPropressThread()
{
	delete _Thread;
	_Thread = nullptr;
}

uint32 FJoyCheckPropressThread::Run()
{
	FPlatformProcess::Sleep(2.0f);
	while (_stopTaskCounter.GetValue() == 0)
	{
		if (IsFinishedLoad())
		{
			break;
		}
		FPlatformProcess::Sleep(0.01f);
	}
	return 0;
}

bool FJoyCheckPropressThread::Init()
{
	_loadedLevels.Empty();
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString(TEXT("Thread init ***************")));
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString(TEXT("Check Async Loading Level Thread Started")));
	return true;
}

void FJoyCheckPropressThread::Stop()
{
	_stopTaskCounter.Increment();
}

void FJoyCheckPropressThread::Exit()
{
	if (FJoyCheckPropressThread::IsFinishedLoad())
	{
		FJoyCheckPropressThread::ShutDown();
	}
}

void FJoyCheckPropressThread::EnSureCompletion()
{
	Stop();
	_Thread->WaitForCompletion();
}

void FJoyCheckPropressThread::ShutDown()
{
	if (_Runnable)
	{
		_Runnable->EnSureCompletion();
		delete _Runnable;
		_Runnable = nullptr;
		UE_LOG(LogTemp, Error, TEXT("runable shutdown "));
	}
}

FJoyCheckPropressThread * FJoyCheckPropressThread::JoyInitAsyncCheck(TArray<FName> LevelNames, ASceneManagerActor * SceneManager)
{
	if (!_Runnable && FPlatformProcess::SupportsMultithreading())
	{
		_Runnable = new FJoyCheckPropressThread(LevelNames, SceneManager);
	}
	return _Runnable;
}

bool FJoyCheckPropressThread::IsThreadFinished()
{
	if (_Runnable)
	{
		return _Runnable->LoadingDone();
	}
	return true;
}

