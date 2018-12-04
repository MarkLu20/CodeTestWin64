// Fill out your copyright notice in the Description page of Project Settings.

#include "HttpDownLoadRequst.h"
#include "Paths.h"
#include "FileHelper.h"
#include "DownLoadFileOpera.h"
#include "PlatformFileManager.h"
#include "HttpDelegates.h"



UHttpDownLoadRequst::UHttpDownLoadRequst(const FObjectInitializer& ObjectInitializer)
{
	if (!HasAnyFlags(EObjectFlags::RF_ClassDefaultObject))
	{

		InitSelfData();
	}
}

void UHttpDownLoadRequst::RequsetDownLoad(const FString& ServerAddr, const FString& FileName, EFileType FileType, UHttpDelegates* DelegatesObject, int32 ChunkSize /*1*/, bool DeletetheLoadedFile)
{
	PrivateDelegatesObject = DelegatesObject;
	Address = ServerAddr;
	PrivateChunkSize = ChunkSize * 1024 * 1024;
	ParameterFile = FileName;
	bDeleteLoadedFile = DeletetheLoadedFile;
	SavePath = (*FileFunctionMap.Find(FileType))(FileName);
	PrivateFileType = FileType;
	HttpRequestInstance->HttpRequest(ServerAddr, TEXT("HEAD"), FHttpRequestCompleteDelegate::CreateUObject(this, &UHttpDownLoadRequst::OnGetSizeCompleted));

}

void UHttpDownLoadRequst::StopDownLoad()
{
	ClearSelfData();
	if ((!bPause&&bSucceedGetSize) || bDone)
	{
		if (!bPause)
		{
			bPause = 1;
		}
		if (bDone)
		{
			bPause = 0;
		}
		if(HttpRequestInstance)
		{
			
			HttpRequestInstance->ShutDownRequest();
		}
		
	}

	//SavePath.Empty();

}

void UHttpDownLoadRequst::ContinueDownload()
{
	if (bPause)
	{
		bPause = 0;
		RequsetDownLoad(Address, ParameterFile, PrivateFileType, PrivateDelegatesObject, PrivateChunkSize / 1024 / 1024);
	}
}

UHttpDownLoadRequst::~UHttpDownLoadRequst()
{
	bDone = 1;
	StopDownLoad();
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
	bDone = 0;
	bSucceedGetSize = 0;
	bPause = 0;
	bDeleteLoadedFile = 0;
	HttpRequestInstance = NewObject<UHttpRequest>();
	FileFunctionMap.Add(EFileType::RelativeProjectPath, [this](const FString& Path) {   return this->GetRelativeProjectPath(Path);   });
	FileFunctionMap.Add(EFileType::AbsolutePath, [this](const FString& Path) {  return this->GetAbsolutePath(Path);  });
	DownLoadFileOpera = UDownLoadFileOpera::Get();


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

void UHttpDownLoadRequst::OnGetSizeCompleted(FHttpRequestPtr InRequest, FHttpResponsePtr InResponse, bool bWasSuccessful)
{
	int64 TempSize = 0;

	int32 ReturnCode = InResponse->GetResponseCode();
	if (200 == ReturnCode)
	{
		TotalSize = InResponse->GetContentLength();
		PrivateDelegatesObject->GetDownLoadRemoteSize.Broadcast(TotalSize);
		bSucceedGetSize = 1;
		FString FileCleanName = FPaths::GetCleanFilename(InResponse->GetURL());
		ServerCleanUpName = SavePath += FileCleanName;
		TempSize = DownLoadFileOpera->GetFileSize(*ServerCleanUpName);
		if (TempSize >= TotalSize)
		{
			if (bDeleteLoadedFile)
			{
				DownLoadFileOpera->DeleteFile(ServerCleanUpName);

			}
			else
			{
				return;
			}
		}
		SetCurrentSize();
		StartDownLoad();

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
		PrivateDelegatesObject->GetDownLoadPercentageDel.Broadcast(Percentage);
		StartDownLoad();
	}
	else
	{
		OnDownLoaded();
	}
}

void UHttpDownLoadRequst::OnDownLoaded()
{
	bDone = 1;
	StopDownLoad();
	PrivateDelegatesObject->GetDownLoadPercentageDel.Broadcast(100.0f);
	PrivateDelegatesObject->DownLoadDoneDel.Broadcast();


}

void UHttpDownLoadRequst::SetCurrentSize()
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
}

void UHttpDownLoadRequst::StartDownLoad()
{
	FString FilePath = SavePath;//+ FPaths::GetCleanFilename(Address);
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
	HttpRequestInstance->HttpRequest(Address, TEXT("GET"), FHttpRequestCompleteDelegate::CreateUObject(this, &UHttpDownLoadRequst::OnRepquestCompelete), FHttpRequestProgressDelegate(), FString("Range"), RangeStr);

}