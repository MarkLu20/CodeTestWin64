// Fill out your copyright notice in the Description page of Project Settings.

#include "HttpDownloadManager.h"
#include "HttpDelegates.h"
#if UE_EDITOR //+UE_BUILD_DEBUG + UE_BUILD_DEVELOPMENT + UE_BUILD_TEST + UE_BUILD_SHIPPING)
#include "Editor.h"
#endif
DEFINE_LOG_CATEGORY(HttpDownloadManagerLog);
void UHttpDownloadManager::InitSelfData()
{
#if UE_EDITOR
	FEditorDelegates::PrePIEEnded.AddUObject(this, &UHttpDownloadManager::OnEditorEndPlay);
#endif
}

UHttpDownloadManager* UHttpDownloadManager::HttpDownLoadManager = nullptr;
UHttpDownloadManager::UHttpDownloadManager()
{
	InitSelfData();
}

UHttpDownloadManager::~UHttpDownloadManager()
{
	
}

void UHttpDownloadManager::RequsetDownLoad(const FString& ServerAddr, const FString& FileName, EFileType FileType, int32 GUID, int32 ChunkSize /*= 1*/, bool DeletetheLoadedFile)
{
	if (RequestMap.Find(GUID))
	{
		UE_LOG(HttpDownloadManagerLog, Fatal, TEXT("GUID ÷ÿ∏¥"));
	}
	Request = NewObject<UHttpDownLoadRequst>();
	Request->AddToRoot();
	DelegatesObject = NewObject<UHttpDelegates>();
	DelegatesObject->AddToRoot();
	Request->RequsetDownLoad(ServerAddr, FileName, FileType, DelegatesObject, ChunkSize, DeletetheLoadedFile);
	RequestMap.Add(GUID, Request);
	DelegatesObjectMap.Add(GUID, DelegatesObject);
}

void UHttpDownloadManager::StopDwonLoad(int32 GUID)
{
	if (RequestMap.Num() > 0)
	{
		(*RequestMap.Find(GUID))->StopDownLoad();
	}

}

void UHttpDownloadManager::ContinueDownload(int32 GUID)
{
	if (RequestMap.Num() > 0)
	{
		(*RequestMap.Find(GUID))->ContinueDownload();
	}

}

UHttpDelegates* UHttpDownloadManager::GetDownLoadDelegateObejct(int32 GUID)
{
	if (DelegatesObjectMap.Num() > 0)
	{
		return  (*DelegatesObjectMap.Find(GUID));
	}
	return nullptr;

}

UHttpDownloadManager* UHttpDownloadManager::Get()
{
	if (IsInGameThread() && HttpDownLoadManager == nullptr)
	{
		HttpDownLoadManager = NewObject<UHttpDownloadManager>();
		HttpDownLoadManager->AddToRoot();
	}
	return HttpDownLoadManager;
}

#if UE_EDITOR
void UHttpDownloadManager::OnEditorEndPlay(bool bIsSimulating)
{
	if (HttpDownLoadManager)
	{
		HttpDownLoadManager->RemoveFromRoot();
		HttpDownLoadManager = nullptr;
	}
	if (RequestMap.Num() > 0)
	{
		for (const auto& RequestValue : RequestMap)
		{
			RequestValue.Value->StopDownLoad();
		}
	}
	UE_LOG(HttpDownloadManagerLog, Log, TEXT("EditorEndPlay"));
}
#endif 