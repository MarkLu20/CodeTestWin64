// Fill out your copyright notice in the Description page of Project Settings.

#include "DownLoadFileOpera.h"
#include "PlatformFileManager.h"
#include "GenericPlatformFile.h"
#if UE_EDITOR
#include "Editor.h"
#endif


UDownLoadFileOpera* UDownLoadFileOpera::DownLoadFileOpera = nullptr;
UDownLoadFileOpera::UDownLoadFileOpera()
{
	InitSelfData();
}

UDownLoadFileOpera::~UDownLoadFileOpera()
{
	DownLoadFileOpera = nullptr;
}

UDownLoadFileOpera* UDownLoadFileOpera::Get()
{
	if (IsInGameThread() && DownLoadFileOpera == nullptr)
	{
		DownLoadFileOpera = NewObject<UDownLoadFileOpera>();
		DownLoadFileOpera->AddToRoot();
	}
	return DownLoadFileOpera;
}

void UDownLoadFileOpera::InitSelfData()
{
	if (PlatformFile == nullptr)
	{
		PlatformFile = &FPlatformFileManager::Get().GetPlatformFile();
		if (PlatformFile->GetLowerLevel())
		{
			PlatformFile = PlatformFile->GetLowerLevel();
		}
	}
#if UE_EDITOR
	FEditorDelegates::PrePIEEnded.AddUObject(this, &UDownLoadFileOpera::EditorEndPlay);
#endif // WITH_EDITOR

}

IPlatformFile* UDownLoadFileOpera::GetPlatformFile()
{

	return PlatformFile;
}

int64 UDownLoadFileOpera::GetFileSize(const FString& File)
{
	if (PlatformFile)
	{
		if (PlatformFile->FileExists(*File))
		{
			FileSize = PlatformFile->FileSize(*File);

		}
		else
		{
			return -1;
		}

	}
	return FileSize;
}

bool UDownLoadFileOpera::DeleteFile(const FString& File)
{
	return PlatformFile->DeleteFile(*File);

}

IFileHandle* UDownLoadFileOpera::OpenWriteFile(const FString& File, bool bAppend /*= false*/, bool bAllowRead /*= false*/)
{
	return PlatformFile->OpenWrite(*File, bAppend, bAllowRead);
}

bool UDownLoadFileOpera::MoveFile(const FString& ToFile, const FString& FromFile)
{
	return PlatformFile->MoveFile(*ToFile, *FromFile);

}

#if UE_EDITOR
void UDownLoadFileOpera::EditorEndPlay(bool bIsSimulating)
{
	if (DownLoadFileOpera)
	{
		DownLoadFileOpera->RemoveFromRoot();
	}

}
#endif // WITH_EDITOR