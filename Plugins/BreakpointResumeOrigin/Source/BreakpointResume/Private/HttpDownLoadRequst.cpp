// Fill out your copyright notice in the Description page of Project Settings.

#include "HttpDownLoadRequst.h"
#include "Paths.h"
#include "FileHelper.h"
#include "DownLoadFileOpera.h"
#include "PlatformFileManager.h"
#include "HttpManager.h"
#ifdef WITH_EDITOR
#include "Editor.h"
#endif
#include "HttpDelegates.h"

UHttpDownLoadRequst* UHttpDownLoadRequst::HttpDownLoadRequst = nullptr;
UHttpDownLoadRequst::UHttpDownLoadRequst()
{

	FString test;
	InitSelfData();

}

void UHttpDownLoadRequst::RequsetDownLoad(const FString& ServerAddr, const FString& FileName, EFileType FileType, int32 ChunkSize /*5*/, bool AddDownloadingExtension /*= true*/, const FString& DownloadingExtension/* = TEXT("Downloading")*/)
{

	bAddDownloadingExtension = AddDownloadingExtension;
	Address = ServerAddr;
	PrivateChunkSize = ChunkSize * 1024 * 1024;
	ParameterFile = FileName;
	SavePath = (*FileFunctionMap.Find(FileType))(FileName);
	PrivateExtension = DownloadingExtension;
	PrivateFileType = FileType;
	TSharedRef<IHttpRequest> HttpRequestSize = FHttpModule::Get().CreateRequest();
	HttpRequestSize->SetVerb("HEAD");
	HttpRequestSize->SetURL(ServerAddr);
	FHttpModule::Get().GetHttpManager().AddRequest(HttpRequestSize);
	HttpRequestSize->OnProcessRequestComplete().BindUObject(this, &UHttpDownLoadRequst::OnGetSizeCompleted);
	HttpRequestSize->ProcessRequest();


}

void UHttpDownLoadRequst::StopDownLoad()
{
	bPause = 1;
	ClearSelfData();
	if (HttpSharedPtr.IsValid())
	{
		HttpSharedPtr->CancelRequest();
		FHttpModule::Get().GetHttpManager().RemoveRequest(HttpSharedPtr.ToSharedRef());
		if (HttpSharedPtr->OnProcessRequestComplete().IsBound())
		{
			HttpSharedPtr->OnProcessRequestComplete().Unbind();
		}

		FHttpModule::Get().GetHttpManager().Flush(true);
	}
	//SavePath.Empty();

}

void UHttpDownLoadRequst::ContinueDownload()
{
	RequsetDownLoad(Address, ParameterFile, PrivateFileType, PrivateChunkSize / 1024 / 1024, bAddDownloadingExtension, PrivateExtension);
}

UHttpDownLoadRequst* UHttpDownLoadRequst::Get()
{
	if (IsInGameThread() && HttpDownLoadRequst == nullptr)
	{
		HttpDownLoadRequst = NewObject<UHttpDownLoadRequst>();
		HttpDownLoadRequst->AddToRoot();
	}
	if (!IsInGameThread())
	{
		UE_LOG(LogTemp, Warning, TEXT("The download is already an asynchronous thread "));
	}
	return HttpDownLoadRequst;
}

UHttpDownLoadRequst::~UHttpDownLoadRequst()
{
	StopDownLoad();
	HttpDownLoadRequst = nullptr;
}


FString UHttpDownLoadRequst::GetRelativeProjectPath(const FString& Path)
{
	int32 Index;
	FString TempPath;
	TempPath = FString(TEXT("/"));
	if (!Path.FindLastChar(**TempPath, Index))
	{
		TempPath = Path;
		TempPath += FString(TEXT("/"));
	}
	else
	{
		TempPath = Path;
	}
	SavePath = FPaths::ProjectDir() / *TempPath;
	return SavePath;

}

FString UHttpDownLoadRequst::GetAbsolutePath(const FString& Path)
{


	return SavePath;
}

void UHttpDownLoadRequst::InitSelfData()
{
	bPause = 0;
	FileFunctionMap.Add(EFileType::RelativeProjectPath, [this](const FString& Path) {   return this->GetRelativeProjectPath(Path);   });
	FileFunctionMap.Add(EFileType::AbsolutePath, [this](const FString& Path) {  return this->GetAbsolutePath(Path);  });
	DownLoadFileOpera = UDownLoadFileOpera::Get();
#ifdef WITH_EDITOR
	FEditorDelegates::PrePIEEnded.AddUObject(this, &UHttpDownLoadRequst::OnEditorEndPlay);
#endif // WITH_EDITOR


}

void UHttpDownLoadRequst::ClearSelfData()
{
	if (TargetFile)
	{
		TargetFile->Flush();
		delete TargetFile;
		TargetFile = nullptr;

	}
}

void UHttpDownLoadRequst::OnGetSizeCompleted(TSharedPtr<IHttpRequest> InRequest, TSharedPtr<IHttpResponse, ESPMode::ThreadSafe> InResponse, bool bWasSuccessful)
{
	int64 TempSize = 0;

	int32 ReturnCode = InResponse->GetResponseCode();
	if (200 == ReturnCode)
	{
		TotalSize = InResponse->GetContentLength();
		FString FileCleanName = FPaths::GetCleanFilename(InResponse->GetURL());
		ServerCleanUpName = SavePath + FileCleanName;
		TempSize = DownLoadFileOpera->GetFileSize(*ServerCleanUpName);
		if (bAddDownloadingExtension)
		{
			ServerCleanUpName += PrivateExtension;
		}



		if (TempSize < TotalSize)
		{
			TargetFile = DownLoadFileOpera->OpenWriteFile(*ServerCleanUpName, true);
			if (TargetFile == nullptr)
			{
				UE_LOG(LogTemp, Error, TEXT(" OpenFile Error"));
			}
			else
			{
				CurrentSize = TargetFile->Size();
			}
			if (TempSize < TotalSize)
			{
				StartDownLoad();
			}

		}





	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Http Error Code  : %d"), ReturnCode);

		//ClearSelfData();

	}
}

void UHttpDownLoadRequst::OnRepquestCompelete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded)
{
	TArray<uint8> ContextRe = HttpResponse->GetContent();
	FString Path = FPaths::GetCleanFilename(HttpResponse->GetURL());
	DataBuffer = HttpResponse->GetContent();
	if (TargetFile)
	{
		TargetFile->Seek(CurrentSize);
		bool Write = this->TargetFile->Write(DataBuffer.GetData(), DataBuffer.Num());
		if (Write)
		{
			TargetFile->Flush();
			OnChunkLoaded(DataBuffer.Num());
		}
	}
}

void UHttpDownLoadRequst::OnChunkLoaded(int32 DataSize)
{
	CurrentSize = DataSize + CurrentSize;
	if (CurrentSize < TotalSize)
	{
		float Percentage = CurrentSize / static_cast<float>(TotalSize);
		UHttpDelegates::Get()->GetDownLoadPercentageDel.Broadcast(Percentage);
		StartDownLoad();
	}
	else
	{
		OnDownLoaded();
	}
}

void UHttpDownLoadRequst::OnDownLoaded()
{
	if (bAddDownloadingExtension)
	{
		DownLoadFileOpera->MoveFile(*ServerCleanUpName, *SavePath);
	}
	UHttpDelegates::Get()->GetDownLoadPercentageDel.Broadcast(100.0f);
	UHttpDelegates::Get()->DownLoadDoneDel.Broadcast();
	StopDownLoad();

}
#ifdef WITH_EDITOR
void UHttpDownLoadRequst::OnEditorEndPlay(bool bIsSimulating)
{
	if (HttpDownLoadRequst)
	{
		HttpDownLoadRequst->RemoveFromRoot();
	}

}
#endif 
void UHttpDownLoadRequst::StartDownLoad()
{
	FString FilePath = SavePath;//+ FPaths::GetCleanFilename(Address);
	TSharedRef<IHttpRequest> HttpRequestDownLoad = FHttpModule::Get().CreateRequest();
	HttpSharedPtr = HttpRequestDownLoad->AsShared();
	FHttpModule::Get().GetHttpManager().AddRequest(HttpSharedPtr.ToSharedRef());
	HttpSharedPtr->SetURL(Address);
	HttpSharedPtr->SetVerb(TEXT("GET"));
	int32 DownLoadStartPosition = CurrentSize;
	int32 DownLoadEndPostion = DownLoadStartPosition + PrivateChunkSize - 1;
	if (DownLoadEndPostion >= TotalSize)
	{
		DownLoadEndPostion = TotalSize - 1;
	}
	if (DownLoadStartPosition >= DownLoadEndPostion)
	{
		UE_LOG(LogTemp, Error, TEXT("Its Error! DownLoadStartPosition >= DownLoadEndPostion"));
		return;
	}

	FString RangeStr = FString("bytes=") + FString::FromInt(DownLoadStartPosition) + FString(TEXT("-")) + FString::FromInt(DownLoadEndPostion);
	HttpSharedPtr->SetHeader(FString("Range"), RangeStr);
	HttpSharedPtr->OnProcessRequestComplete().BindUObject(this, &UHttpDownLoadRequst::OnRepquestCompelete);
	HttpSharedPtr->ProcessRequest();
}
