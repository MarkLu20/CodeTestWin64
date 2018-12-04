// Fill out your copyright notice in the Description page of Project Settings.

#include "HttpObject.h"
#include "Json.h"
#include "HttpManager.h"
#include "FileHelper.h"
#include "Paths.h"
#include "Engine.h"
#include "PlatformFileManager.h"
#define LOCTEXT_NAMESPACE "UHTTPOBJECT" 

void UHttpObject::OnWriteChunkEnd(int32 DataSize)
{
	CurrentSize = DataSize+CurrentSize;
	if (CurrentSize < TotalSize)
	{
		
		//download next chunk
		float Percentage = CurrentSize / TotalSize;
		UE_LOG(LogTemp, Warning, TEXT("f"),Percentage);
		DownLoad();
	}
	else
	{
		OnTaskCompleted();
	}
}

void UHttpObject::SetTotalSize(int32 totalsize)
{
	TotalSize = totalsize;
}

void UHttpObject::OnTaskCompleted()
{
	if (TargetFile)
	{
		TargetFile->Flush();
		delete TargetFile;
		TargetFile = nullptr;
	}
	if (PlatformFile->MoveFile(*CleanUpFilePath,*TempPath))
	{
		UE_LOG(LogTemp, Warning, TEXT("%s, completed !"), *CleanUpFilePath);
	}
}

UHttpObject* UHttpObject::httpObject = nullptr;
void UHttpObject::DownLoad()
{
	/*HttpObject = NewObject<UHttpObject>();
	HttpObject->AddToRoot();*/
	
	
	
	FString FilePath = FPaths::ProjectDir() / *(FileNameTag + FPaths::GetCleanFilename(Address));
	/*if (FPlatformFileManager::Get().GetPlatformFile().DirectoryExists(*FilePath))
	{
	  CurrentSize=  static_cast<int32>(FPlatformFileManager::Get().GetPlatformFile().FileSize(*FilePath));
	}
	else
	{
		CurrentSize = 0;
	}*/
	
	/*const FWorldContext *Context = *GEngine->GetWorldContexts().GetData();
	UWorld *World = Context->World();*/
	 TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	 HttpSharedPtr = HttpRequest->AsShared();
	//添加到HTTPMangerThread线程中
	
	 FHttpModule::Get().GetHttpManager().AddRequest(HttpSharedPtr.ToSharedRef());
	
	 HttpSharedPtr->SetURL(Address);
	 HttpSharedPtr->SetVerb(TEXT("GET"));
	/*FString Path= "Config/QQ9.0.6.24044.exe";
	Path = FPaths::ProjectDir() / *Path;*/
	

	int32 StartPostion = CurrentSize;
	int32 EndPosition = StartPostion + ChunkSize - 1;;
	if (EndPosition >= TotalSize)
	{
		EndPosition = TotalSize - 1;
	}
	if (StartPostion >= EndPosition)
	{
		UE_LOG(LogTemp, Warning, TEXT("Error! StartPostion >= EndPosition"));
		return;
	}
	FString RangeStr = FString("bytes=") + FString::FromInt(StartPostion)+ FString(TEXT("-"))+ FString::FromInt(EndPosition);
	HttpSharedPtr->SetHeader(FString("Range"),RangeStr);

	//HttpRequest->SetHeader(TEXT("User-Agent"), TEXT("X-UnrealEngine-Agent"));
	
	/*HttpRequest->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	HttpRequest->SetHeader(TEXT("Accepts"), TEXT("application/json"));*/
	//HttpRequest->SetHeader(TEXT("Accepts"), TEXT("application/json"));
	//HttpRequest->SetContentAsString(ServerAddr);
	HttpSharedPtr->OnRequestProgress().BindUObject(this,&UHttpObject::HandleHttpProgress);
	HttpSharedPtr->OnProcessRequestComplete().BindUObject(this,&UHttpObject::RepquestCompelete);
	HttpSharedPtr->ProcessRequest();
	//FHttpModule::Get().GetHttpManager().Initialize();
	
}

void UHttpObject::SetStop()
{
	bPause = true;
	if (TargetFile)
	{
		TargetFile->Flush();
		delete TargetFile;
		TargetFile = nullptr;
	}
	if (HttpSharedPtr.IsValid())
	{
		HttpSharedPtr->CancelRequest();
		FHttpModule::Get().GetHttpManager().RemoveRequest(HttpSharedPtr.ToSharedRef());
		if (HttpSharedPtr->OnProcessRequestComplete().IsBound())
		{
			HttpSharedPtr->OnProcessRequestComplete().Unbind();
		}


	}
	FHttpModule::Get().GetHttpManager().Flush(true);
}

void UHttpObject::Continue()
{
	bPause = false;
	RequsetDownLoadFile(Address, FileNameTag);
}

UHttpObject::UHttpObject()
{
	if (PlatformFile == nullptr)
	{
		PlatformFile = &FPlatformFileManager::Get().GetPlatformFile();
		if (PlatformFile->GetLowerLevel())
		{
			PlatformFile = PlatformFile->GetLowerLevel();
		}
	}
	if (TargetFile)
	{
		TargetFile->Flush();
		delete TargetFile;
		TargetFile = nullptr;
	}

}

UHttpObject::~UHttpObject()
{
	if (TargetFile)
	{
		TargetFile->Flush();
		delete TargetFile;
		TargetFile = nullptr;
	}
}

void UHttpObject::RequsetDownLoadFile(FString ServerAddr,FString FileName)
{   
	
	CleanUpFilePath = FPaths::ProjectDir() / *(FileName + FPaths::GetCleanFilename(ServerAddr));
	TSharedRef<IHttpRequest> HttpRequestSize = FHttpModule::Get().CreateRequest();
	HttpRequestSize->SetVerb("HEAD");
	HttpRequestSize->SetURL(ServerAddr);
	FileNameTag = FileName;
	Address = ServerAddr;
	FHttpModule::Get().GetHttpManager().AddRequest(HttpRequestSize);
	HttpRequestSize->OnProcessRequestComplete().BindUObject(this,&UHttpObject::OnGetHeadCompleted);
	HttpRequestSize->ProcessRequest();
}

void UHttpObject::RepquestCompelete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded)
{
	//httpObject->RemoveFromRoot();
	
	
	if (bPause)
	{
		if (TargetFile)
		{
			TargetFile->Flush();
			delete TargetFile;
			TargetFile = nullptr;
		}
		return;
	}
	TArray<uint8> ContextRe = HttpResponse->GetContent();
	FString Path = FPaths::GetCleanFilename(HttpResponse->GetURL());
	
	FString temp = FileNameTag + FPaths::GetCleanFilename(HttpResponse->GetURL())+".temp";
	FString FilePath = FPaths::ProjectDir() / *temp;

	DataBuffer= HttpResponse->GetContent();
	if (TargetFile)
	{
		this->TargetFile->Seek(CurrentSize);
		bool bWriteRet = this->TargetFile->Write(DataBuffer.GetData(), DataBuffer.Num());
		if (bWriteRet)
		{
			this->TargetFile->Flush();
			this->OnWriteChunkEnd(this->DataBuffer.Num());
		}
	}
	

}


void UHttpObject::HandleHttpProgress(FHttpRequestPtr req, int32 uploaded, int32 downloaded)
{
	
	FString Path = FPaths::GetCleanFilename(req->GetResponse()->GetURL());
	Path = "Config/" + Path;
	Path = FPaths::ProjectDir() / *Path;
	//ElapsedDel.Broadcast(uploaded/downloaded);
	/*FFileHelper::SaveArrayToFile(Content, *Path);*/
	float prosse = downloaded / TotalSize;
	FString File = FileNameTag + FPaths::GetCleanFilename(req->GetURL());
	FString FilePath = FPaths::ProjectDir() / *File;
	
	
	UE_LOG(LogTemp, Error, TEXT("%f"), prosse);
}

UHttpObject * UHttpObject::GetHttpObject()
{
	if (httpObject == nullptr)
	{
		httpObject = NewObject<UHttpObject>();
		httpObject->AddToRoot();
	}
	return httpObject;
}
void UHttpObject::ShutDownHttpThread()
{  //关闭http模块
	
	bPause = true;
	/*if (httpObject)
	{
		httpObject->RemoveFromRoot();
	}*/

	if (TargetFile)
	{
		TargetFile->Flush();
	}
	if (HttpSharedPtr.IsValid())
	{
		HttpSharedPtr->CancelRequest();
		FHttpModule::Get().GetHttpManager().RemoveRequest(HttpSharedPtr.ToSharedRef());
		if (HttpSharedPtr->OnProcessRequestComplete().IsBound())
		{
			HttpSharedPtr->OnProcessRequestComplete().Unbind();
		}
	
		
	}
	FHttpModule::Get().GetHttpManager().Flush(true);
	delete TargetFile;
	TargetFile = nullptr;
}

void UHttpObject::OnGetHeadCompleted(TSharedPtr<IHttpRequest> InRequest, TSharedPtr<IHttpResponse, ESPMode::ThreadSafe> InResponse, bool bWasSuccessful)
{
	int32 RetutnCode = InResponse->GetResponseCode();
	if (RetutnCode >= 400 || RetutnCode < 200)
	{
		UE_LOG(LogTemp, Warning, TEXT("Http return code error : %d"), RetutnCode);
		if (TargetFile != nullptr)
		{
			delete TargetFile;
			TargetFile = nullptr;
		}
	}
	if (InResponse->GetResponseCode()==200)
	{
		FString File = FileNameTag + FPaths::GetCleanFilename(InResponse->GetURL());
		FString FilePath = FPaths::ProjectDir() / *File;
		TotalSize = InResponse->GetContentLength();
		TempPath = FilePath + TEXT(".dlFile");
		TargetFile = PlatformFile->OpenWrite(*TempPath,true);
		if (TargetFile==nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT(" create temp file error !"));
			return;
		}
		else
		{
			CurrentSize = TargetFile->Size();
		}
		/*if (InResponse->GetHeader("ETag") .IsEmpty())
		{
			SetETag(InResponse->GetHeader(FString("ETag")));
			SetCurrentSize(0);
		}*/
		DownLoad();
	}
	UE_LOG(LogTemp, Error, TEXT("%d"), TotalSize);

}

void UHttpObject::BeginDestroy()
{
	Super::BeginDestroy();
	if (TargetFile)
	{
		TargetFile->Flush();
		delete TargetFile;
		TargetFile = nullptr;
	}
}

#undef LOCTEXT_NAMESPACE 
//if (bSucceeded)
//{
	// int32 code=HttpResponse->GetResponseCode();
	//TArray<FJsonList> jsonList;
	//FJsonList jsondata;
	//TArray<TSharedPtr<FJsonValue>> JsonParsed;
	//TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(HttpResponse->GetContentAsString());
	//if (FJsonSerializer::Deserialize(JsonReader, JsonParsed))
	//{  
	//	
	//	for (size_t i = 0; i < JsonParsed.Num(); i++)
	//	{
	//		jsondata.Uid = FString::FromInt(JsonParsed[i]->AsObject()->GetIntegerField("uid"));
	//		jsondata.Userid = JsonParsed[i]->AsObject()->GetStringField("userid");
	//		jsondata.UserName = JsonParsed[i]->AsObject()->GetStringField("username");
	//		jsondata.UserPWD = JsonParsed[i]->AsObject()->GetStringField("userpwd");
	//		jsondata.ZoneMark = JsonParsed[i]->AsObject()->GetStringField("zonemark");
	//		jsonList.Add(jsondata);
	//		
	//	}
	//	PassJsonData.Broadcast(jsonList);
	//	//test.Broadcast(FString(TEXT("sadfasdfasdfasdfasdf")));
	//	GetURLData(jsonList);
	//	
//	}


//SS = TCHAR_TO_UTF8(*SS);
//FText aa= FText::FromString(SS);
/*	UE_LOG(LogTemp, Error, TEXT("******************"));
}*/