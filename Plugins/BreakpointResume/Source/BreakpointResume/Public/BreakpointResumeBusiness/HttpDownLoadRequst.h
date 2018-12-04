// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BreakpointResumeNetWork/HttpRequest.h"
#include "HttpDownLoadRequst.generated.h"

/**
 *
 */
UENUM(BlueprintType)
enum class  EFileType :uint8
{
	RelativeProjectPath,
	AbsolutePath,

};

UCLASS(BlueprintType)
class BREAKPOINTRESUME_API UHttpDownLoadRequst : public UObject
{
	GENERATED_BODY()
public:

	UHttpDownLoadRequst(const FObjectInitializer& ObjectInitializer);

	void RequsetDownLoad(const FString& ServerAddr, const FString& FileName, EFileType FileType, class UHttpDelegates* DelegatesObject, int32 ChunkSize = 1, bool DeletetheLoadedFile = true);

	void StartDownLoad();

	void StopDownLoad();

	void ContinueDownload();

	~UHttpDownLoadRequst();


private:
	TMap<EFileType, TFunction< FString(const FString&)  > > FileFunctionMap;

	FString GetRelativeProjectPath(const FString& Path);

	FString GetAbsolutePath(const FString& Path);
	FString SavePath;
	FString Address;
	FString ServerCleanUpName;
	FString ParameterFile;
	int32 TotalSize = 0;
	int32 CurrentSize = 0;
	int32 PrivateChunkSize = 0;
	EFileType PrivateFileType : 1;
	IFileHandle* TargetFile = nullptr;
	class UDownLoadFileOpera* DownLoadFileOpera = nullptr;
	TMap<int32, UHttpDownLoadRequst* >HttpDownloadMap;
	class UHttpDelegates* PrivateDelegatesObject = nullptr;
	TArray<uint8> DataBuffer;
	uint32 bPause : 1;
	uint32 bSucceedGetSize : 1;
	uint32 bDone : 1;
	uint32 bDeleteLoadedFile : 1;
	UPROPERTY()
		UHttpRequest* HttpRequestInstance = nullptr;

private:
	void InitSelfData();
	void ClearSelfData();
	void OnGetSizeCompleted(FHttpRequestPtr InRequest, FHttpResponsePtr InResponse, bool bWasSuccessful);
	void OnRepquestCompelete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded);
	void OnChunkLoaded(int32 DataSize);
	void OnDownLoaded();
	void SetCurrentSize();

};
