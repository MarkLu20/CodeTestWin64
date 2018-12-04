// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Http.h"
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

UCLASS()
class BREAKPOINTRESUME_API UHttpDownLoadRequst : public UObject
{
	GENERATED_BODY()

public:
	UHttpDownLoadRequst();
	UFUNCTION(BlueprintCallable)
		void RequsetDownLoad(const FString& ServerAddr, const FString& FileName, EFileType FileType, int32 ChunkSize = 1,bool AddDownloadingExtension=false,const FString& DownloadingExtension = TEXT(".Downloading"));
	UFUNCTION(BlueprintCallable)
		void StartDownLoad();
	UFUNCTION(BlueprintCallable)
		void StopDownLoad();
	UFUNCTION(BlueprintCallable)
		void ContinueDownload();
	UFUNCTION(BlueprintCallable)
		static UHttpDownLoadRequst* Get();
	~UHttpDownLoadRequst();
	

private:
	TMap<EFileType, TFunction< FString(const FString&)  > > FileFunctionMap;

	FString GetRelativeProjectPath(const FString& Path);

	FString GetAbsolutePath(const FString& Path);
	FString SavePath;
	FString PrivateExtension;
	FString Address;
	FString ServerCleanUpName;
	FString ParameterFile;
	int32 TotalSize = 0;
	int32 CurrentSize = 0;
	int32 PrivateChunkSize = 0;
	EFileType PrivateFileType : 1;
	uint32 bAddDownloadingExtension : 1;
	IFileHandle* TargetFile = nullptr;
	//IPlatformFile* PlatformFile = nullptr;
	class UDownLoadFileOpera* DownLoadFileOpera = nullptr;
	TSharedPtr<class IHttpRequest> HttpSharedPtr;
	TArray<uint8> DataBuffer;
	uint32 bPause : 1;
	void InitSelfData();
	void ClearSelfData();
	void OnGetSizeCompleted(TSharedPtr<IHttpRequest> InRequest, TSharedPtr<IHttpResponse, ESPMode::ThreadSafe> InResponse, bool bWasSuccessful);
	void OnRepquestCompelete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded);
	void OnChunkLoaded(int32 DataSize);
	void OnDownLoaded();
#ifdef WITH_EDITOR
	void OnEditorEndPlay(bool bIsSimulating);
#endif
	static UHttpDownLoadRequst* HttpDownLoadRequst;
};
