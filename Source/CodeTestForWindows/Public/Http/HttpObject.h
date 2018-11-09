// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Http.h"
#include "HttpObject.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FJsonList
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite)
		FString Uid;
	UPROPERTY(BlueprintReadWrite)
		FString Userid;
	UPROPERTY(BlueprintReadWrite)
		FString UserName;
	UPROPERTY(BlueprintReadWrite)
		FString UserPWD;
	UPROPERTY(BlueprintReadWrite)
		FString ZoneMark;
};
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPassJosnData,const TArray<FJsonList>&,JsonList);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTestx, FString, TestString);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FElapsed, float, ElapsedTime);
UCLASS(Blueprintable)
class CODETESTFORWINDOWS_API UHttpObject : public UObject
{
	GENERATED_BODY()

public:
	UHttpObject();
	~UHttpObject();
		UFUNCTION(BlueprintCallable)
		void RequsetDownLoadFile(FString ServerAddr,FString FileName);
		void DownLoad();
		UFUNCTION(BlueprintCallable)
		void SetStop();
		UFUNCTION(BlueprintCallable)
		//************************************
		// Method:    Continue
		// FullName:  UHttpObject::Continue
		// Access:    public 
		// Returns:   void
		// Qualifier:
		// Parameter: FString AddRESS
		// Parameter: FString File
		//************************************
		void Continue();
		void RepquestCompelete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded);
		//void PostRepquestCompelete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded);
		void HandleHttpProgress(FHttpRequestPtr req, int32 uploaded, int32 downloaded);
		UPROPERTY(BlueprintAssignable)
			FPassJosnData PassJsonData;
		UPROPERTY(BlueprintAssignable)
			FTestx test;
		UPROPERTY(BlueprintAssignable)
		FElapsed ElapsedDel;
		UFUNCTION(BlueprintCallable)
			static	UHttpObject* GetHttpObject();
		UFUNCTION(BlueprintImplementableEvent,BlueprintCallable)
			void GetURLData(TArray<FJsonList> &jsonlist);
		UFUNCTION(BlueprintCallable)
			void ShutDownHttpThread();
		
		void OnGetHeadCompleted(TSharedPtr<IHttpRequest> InRequest, TSharedPtr<IHttpResponse, ESPMode::ThreadSafe> InResponse, bool bWasSuccessful);

		virtual void BeginDestroy() override;

private:
	void OnWriteChunkEnd(int32 DataSize);
	void SetTotalSize(int32 totalsize);
	void OnTaskCompleted();
	
		static UHttpObject *httpObject;
		UHttpObject *HttpObject = nullptr;
		  UHttpObject* const p =HttpObject;
		  TSharedPtr<class IHttpRequest> HttpSharedPtr;
		  FString RemoteFullname;
		  int32 TotalSize;
		  int32 CurrentSize;
		   int32 ChunkSize = 2 * 1024 * 1024;
		   FString FileNameTag;
		   IFileHandle* TargetFile = nullptr;
		   TArray<uint8> DataBuffer;
		   FString Address;
		   FString CleanUpFilePath;
		   FString TempPath;
		   IPlatformFile* PlatformFile = nullptr;
		   bool bPause = false;
};
