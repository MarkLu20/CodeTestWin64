// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DownLoadFileOpera.generated.h"

/**
 *
 */
UCLASS()
class BREAKPOINTRESUME_API UDownLoadFileOpera : public UObject
{
	GENERATED_BODY()
public:
	UDownLoadFileOpera();
	~UDownLoadFileOpera();


	static UDownLoadFileOpera* Get();
	void InitSelfData();
	IPlatformFile* GetPlatformFile();
	int64 GetFileSize(const FString& File);
	bool DeleteFile(const FString& File);
	IFileHandle* OpenWriteFile(const FString& File, bool bAppend = false, bool bAllowRead = false);
	bool MoveFile(const FString& ToFile, const FString& FromFile);
#if UE_EDITOR
	void EditorEndPlay(bool bIsSimulating);
#endif 

private:
	IPlatformFile* PlatformFile = nullptr;
	int64 FileSize = -1;
	static UDownLoadFileOpera* DownLoadFileOpera;
};
