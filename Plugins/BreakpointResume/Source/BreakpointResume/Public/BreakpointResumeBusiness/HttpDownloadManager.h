// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "HttpDownLoadRequst.h"
#include "HttpDownloadManager.generated.h"

/**
 *
 */
DECLARE_LOG_CATEGORY_EXTERN(HttpDownloadManagerLog, Log, All);
UCLASS(BlueprintType)
class BREAKPOINTRESUME_API UHttpDownloadManager : public UObject
{
	GENERATED_BODY()

public:
	UHttpDownloadManager();
	~UHttpDownloadManager();
	UFUNCTION(BlueprintCallable, Category = HttpDownLoad)
		void RequsetDownLoad(const FString& ServerAddr, const FString& FileName, EFileType FileType, int32 GUID, int32 ChunkSize = 1, bool DeletetheLoadedFile = true);
	UFUNCTION(BlueprintCallable, Category = HttpDownLoad)
		void StopDwonLoad(int32 GUID);
	UFUNCTION(BlueprintCallable, Category = HttpDownLoad)
		void ContinueDownload(int32 GUID);
	UFUNCTION(BlueprintCallable, Category = HttpDownLoad)
		class UHttpDelegates* GetDownLoadDelegateObejct(int32  GUID);
	UFUNCTION(BlueprintCallable, Category = HttpDownLoad)
		static UHttpDownloadManager* Get();
private:
#if UE_EDITOR
	void OnEditorEndPlay(bool bIsSimulating);
#endif
	void InitSelfData();
	TMap<int32, UHttpDownLoadRequst*> RequestMap;
	TMap<int32, class UHttpDelegates*> DelegatesObjectMap;
	UHttpDownLoadRequst* Request = nullptr;
	class UHttpDelegates* DelegatesObject = nullptr;
	static UHttpDownloadManager* HttpDownLoadManager;
};
