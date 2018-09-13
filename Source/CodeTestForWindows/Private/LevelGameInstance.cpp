// Fill out your copyright notice in the Description page of Project Settings.

#include "LevelGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "OpenLevel.h"
#include "Runtime/Engine/Classes/Engine/LevelStreaming.h"
#include "Runtime/CoreUObject/Public/Serialization/AsyncLoading.h"
#include "Runtime/CoreUObject/Private/CoreUObjectPrivatePCH.h"
#include "Runtime/CoreUObject/Private/Serialization/AsyncLoadingThread.h"
#include "Runtime/CoreUObject/Public/CoreUObject.h"
#include "MXLoadingScreen/Public/MXLoadingScreen.h"
#include "Engine.h"
#include "TestObject.h"
#include "OpenFireChatAPI.h"
#include "Runtime/CoreUObject/Public/CoreUObjectSharedPCH.h"
#include "TestObject.h"
#include "LuachuGameProcess.h"

//#define HUIDIAO(X) [X](int val, float valf) { X->Test(val, valf)
//#include "Serialization/AsyncLoadingPrivate.h"

ULevelGameInstance::ULevelGameInstance(/*const FObjectInitializer &ObjectInitializer*/)
{

	//ASceneManagerActor::GetSceneMangerInStance()->InitSceneM(this);
	Index =0;
	
	

}

void ULevelGameInstance::Init()
{
	_tmpDelegate.BindUObject(this, &ULevelGameInstance::LoadAsyncCB);
	TMap<int32, FString> testmap;
	testmap.Add(1, "fsadfad");
	testmap.Add(0,"dfdfsdfa");
	testmap.Add(3,"fsadfsdafsdaffeeeee");
	testmap.KeySort(TGreater<int32>());
	//FCoreUObjectDelegates::OnAssetLoaded.AddUObject(this, &ULevelGameInstance::OnAssetLoadedFunc);
	FCoreUObjectDelegates::PreLoadMap.AddUObject(this, &ULevelGameInstance::ReviceMapName);
	FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this, &ULevelGameInstance::EndMap);
	UPackage::PackageDirtyStateChangedEvent.AddUObject(this,&ULevelGameInstance::DirtyPackage);
	UTestObject *TestObject = NewObject<UTestObject>();
	OpenFire = GetDefault<UOpenFireChatAPI>();
	OpenFire->JoinedRoomArray.Empty();
	UTestObject *Testobjectc = nullptr;
	Testobjectc = UTestObject::GetTestInstance();
	//level
	
	testfuncPointer = [Testobjectc](int val, float valf) { Testobjectc->Test(val, valf); };
	//testfuncPointer=FindFunction(FName("Test"));
	//testfuncPointer = HUIDIAO(UTestObject);
	TMap<FString, TFunction<void(int, float)>> testmape;
	
	testmape.Add(FString("test"), [TestObject](int val, float valf) {TestObject->Test(val, valf); });
	(*testmape.Find(FString("test")))(100, 20.0f);
	
	
}

void ULevelGameInstance::Shutdown()
{
	//OpenFire->RemoveConnection();
}

void ULevelGameInstance::LoadComplete(const float LoadTime, const FString& MapName)
{
	UE_LOG(LogTemp, Error, TEXT(" LoadMap %s %f"), *MapName,LoadTime);
}

void ULevelGameInstance::LoadingCallBack(const FName & _packageName, const TArray<FName>& _allLevelNames, const TArray<FName>& _loadedLevelNames, float _percent)
{
	UE_LOG(LogTemp,Error,TEXT("%s"),_percent);
	GTC(FString("fsafsadfa"));
}

void ULevelGameInstance::OpenLevel()
{
	//FName Loadname(L"/Game/Maps/ThirdPersonExampleMap");
	//LoadPackageAsync(Loadname.ToString(),nullptr,*Loadname.ToString(),_tmpDelegate,EPackageFlags::PKG_ContainsMap,INDEX_NONE);
	//UPackage* package =FindPackage(this, L"/Game/Maps/ThirdPersonExampleMap");
	
	//FString name(L"/Game/Maps/ThirdPersonExampleMap");
	//LoadPackageAsync(name,_tmpDelegate,0,EPackageFlags::PKG_Need, ForceInit);
	
	/*info.CallbackTarget =this;
	info.ExecutionFunction = FName("LoadOver");*/
	//UGameplayStatics::LoadStreamLevel(this,FName("ThirdPersonExampleMap"),true,true, info);
	//ULevelStreaming *level= UGameplayStatics::GetStreamingLevel(this, FName("ThirdPersonExampleMap"));
	//if (level==nullptr)
	//{
	//	ULevelStreaming *level = UGameplayStatics::GetStreamingLevel(this, FName("ThirdPersonExampleMap"));
	//}
	//else
	//{
	//	UE_LOG(LogTemp,Error,TEXT("%s"),*name);
	//}
	

	//FAsyncPackage Packesturct();
	//Packesturct;
	

	if (IsInAsyncLoadingThread)
	{
		//FName testName = name.GetCharArray().GetData();

		//float percentage = GetAsyncLoadPercentage(Loadname);
		//UE_LOG(LogTemp, Error, TEXT("Percentage %f"), percentage);
		


	}
	

	//FJoyCheckPropressThread *Thread = FJoyCheckPropressThread::JoyInitAsyncCheck();
	//UGameplayStatics::LoadStreamLevel(this,FName("ThirdPersonExampleMap"));
	
}

void ULevelGameInstance::LoadAsyncCB(const FName & Name, UPackage * Package, EAsyncLoadingResult::Type Result)
{
	
	
	loadtime+=Package->GetLoadTime();
	Index += 1;
	if (Result==EAsyncLoadingResult::Succeeded&&StreamingArray.Num() != 0 &&Index<StreamingArray.Num())
	{  
		///LoadPackageAsync(StreamingArray[Index]->PackageNameToLoad.ToString() ,_tmpDelegate);
	}	
	if (StreamingArrayNum!=0)
	{
		if ((StreamingArrayNum - 1) == LastLoadIndex)
		{
			UE_LOG(LogTemp, Error, TEXT("Loadtime %f"), loadtime);
			
		}
	}
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, FString(FString::SanitizeFloat(loadtime)));

	
	
}

void ULevelGameInstance::OnAssetLoadedFunc(UObject * LoadedObject)
{
	//UE_LOG(LogTemp, Error, TEXT("Percentage %f"), 10.0f);
	
}

void ULevelGameInstance::LoadOver()
{
	//UE_LOG(LogTemp, Error, TEXT("Percentage %f"), 100.0f);
}

void ULevelGameInstance::ReviceMapName(const FString &MapName)
{
	loadtime = 0;
	ShowLoadingScreen();
	FString MapNameRight;
	FString MapNameLeft;
	int32 index;
	  //MapName.Split("/",&MapNameLeft, &MapNameRight,ESearchCase::CaseSensitive,ESearchDir::FromStart);
	MapName.FindLastChar(L'/', index);
	 int32 TotalIndex = MapName.GetCharArray().Num()-1;
	MapNameRight = MapName.Right(TotalIndex-index-1);
	LoadPackageAsync(MapName, _tmpDelegate);
	UE_LOG(LogTemp, Error, TEXT("ReviceMapName %s"),*MapName);
	
	
}

void ULevelGameInstance::EndMap(UWorld * World)
{

	StreamingArray = World->StreamingLevels;
	//World->FindWorldInPackage();
	
	StreamingArrayNum = StreamingArray.Num();
	//FString test = StreamingArray[0]->PackageNameToLoad.ToString();
	//LoadPackageAsync(StreamingArray[0]->PackageNameToLoad.ToString(), _tmpDelegate);
	for (int32 i = 0; i <StreamingArray.Num(); ++i)
	{
		LastLoadIndex = i;
		FLatentActionInfo info;
		UGameplayStatics::LoadStreamLevel(World->GetFirstPlayerController(), StreamingArray[i]->PackageNameToLoad, true, true, info);
		//LoadPackageAsync(StreamingArray[i]->PackageNameToLoad.ToString(), _tmpDelegate);
		bool loaded = HasLoaded(StreamingArray[i]->PackageNameToLoad);
		
		UE_LOG(LogTemp, Error, TEXT("StreamingLevel %s"), *StreamingArray[i]->PackageNameToLoad.ToString());
		
		
	}
	
	
	
	 
}

void ULevelGameInstance::ShowLoadingScreen()
{
	IMXLoadingScreenModule *const LoadingScreenModule = FModuleManager::LoadModulePtr<IMXLoadingScreenModule>("MXLoadingScreen");
	if (LoadingScreenModule!=nullptr)
	{
		LoadingScreenModule->StartInGameLoadingScreen();
		
	}
}

void ULevelGameInstance::DirtyPackage(UPackage *Package)
{
	UE_LOG(LogTemp, Error, TEXT("ReviceMapName"));
}

void ULevelGameInstance::FindAllUStruct()
{
	TArray<UProperty *> proarray;
	for( TFieldIterator<UProperty> ProIt(GetClass());ProIt;++ProIt)
	{
		proarray.Add(*ProIt);
	}
	UE_LOG(LogTemp,Error,TEXT("fsdfasdf"));
}

void ULevelGameInstance::MixScreen()
{
	UGameEngine *gameEngine = Cast<UGameEngine>(GEngine);
	if (gameEngine)
	{
		TSharedPtr<SWindow> WindowPtr = gameEngine->GameViewportWindow.Pin();
		WindowPtr->Minimize();
	}
}





void ULevelGameInstance::Login(FString ServerAddr, int32 ServerPort, bool bUseSSL, bool bUsePlainTextAuth, float PingInterval, float PingTimeOut, int32 MaxPingRetries, bool bPrivateChatFriendsOnly, const FString &UserID, const FString &Auth)
{
	OpenFire->Login(ServerAddr, ServerPort, bUseSSL, bUsePlainTextAuth, PingInterval, PingTimeOut, MaxPingRetries, bPrivateChatFriendsOnly, UserID, Auth);
    FString guid=FGuid::NewGuid().ToString();
	UE_LOG(LogTemp,Error,TEXT("%s"),*guid);
}

void ULevelGameInstance::SendPrivateMessage(const FString &FromUser, const FString &ToUser, const FString &Msg)
{
	OpenFire->SendPrivateMessage(FromUser, ToUser, Msg);
	
}

void ULevelGameInstance::MucSendMessage(const FString& FromUser, const FString& Message, const FString &Type)
{
	OpenFire->MucSendMessage(FromUser, Message, Type);
}

void ULevelGameInstance::JoinRoom(const FString &Room)
{
	OpenFire->JoinRoom(Room);
}

void ULevelGameInstance::InivteJoinRoom(const FString & FromUser, const FString & ToUser, const FString & RoomName)
{
	//OpenFire->InviteJoinRoom(FromUser,ToUser,RoomName);
}


void ULevelGameInstance::InviteJoinRoom(const FString &FromUser, const FString &ToUser, const FString &RoomName)
{

}

void ULevelGameInstance::Test(int a, float b)
{
	float c = static_cast<float>(a);
	float d = c + b;
	UE_LOG(LogTemp,Error,TEXT("%f floattotal"),d);
}

void ULevelGameInstance::TestFunction()
{
	testfuncPointer(1,100.0f);
}



void ULevelGameInstance::ExcuteExe(const FString &Path)
{
	TWeakObjectPtr<ULuachuGameProcess> lachuptr = GetDefault<ULuachuGameProcess>();
	lachuptr->ExcuteExe(Path);
}

bool ULevelGameInstance::HasLoaded(FName PackageName)
{
	ULevelStreaming *level= UGameplayStatics::GetStreamingLevel(UGameplayStatics::GetPlayerController(this,0),PackageName);
	return level->HasLoadedLevel();
}

