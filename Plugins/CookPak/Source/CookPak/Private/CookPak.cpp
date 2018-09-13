// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "CookPakPrivatePCH.h"
#include "CookPakCommands.h"
#include "AssetRegistryModule.h"
#include "Runtime/Core/Public/HAL/PlatformFilemanager.h"
#include "App.h"

DECLARE_LOG_CATEGORY_EXTERN(ModuleLog, Verbose, All)
DEFINE_LOG_CATEGORY(ModuleLog)

#define LOCTEXT_NAMESPACE "CookPak"

class FMyDirectoryVisitor : public IPlatformFile::FDirectoryVisitor
{
public:
	virtual bool Visit(const TCHAR* Filename, bool IsDirectory)
	{
		if (IsDirectory)
		{
			FString Path(Filename);
			Path.RemoveFromStart(*ParentDirectoryPath);

			// assume all guids have length 32
			if (Path.Len() == 32)
				Directories.Add(Path);
		}
		return true;
	}

	const TArray<FString>& GetDirectoryArray() const
	{
		return Directories;
	}

	void ClearDirectoryArray()
	{
		Directories.Empty();
	}

	void SetParentDirectoryPath(const FString& Path)
	{
		ParentDirectoryPath = Path;
	}

private:
	TArray<FString> Directories;
	FString ParentDirectoryPath;
};

class FCookPak : public ICookPak
{
public:

private:
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	 void AddToolbarExtension(FToolBarBuilder& Builder);
	 void UniqueFolderButtonClicked();
	 void PakAssetsButtonClicked();

private:
	TSharedPtr<FExtender> Extender;
	TSharedPtr<FUICommandList> CommandList;
};

IMPLEMENT_MODULE( FCookPak, CookPak)

void FCookPak::StartupModule()
{
	// This code will execute after your module is loaded into memory (but after global variables are initialized, of course.)
	UE_LOG(ModuleLog, Log, TEXT("CookPak plugin started"));

	FCookPakCommands::Register();
	CommandList = MakeShareable(new FUICommandList);
	CommandList->MapAction(
		FCookPakCommands::Get().UniqueFolderButtonCommand,
		FExecuteAction::CreateRaw(this, &FCookPak::UniqueFolderButtonClicked),
		FCanExecuteAction()
		);
	CommandList->MapAction(
		FCookPakCommands::Get().PakAssetsButtonCommand,
		FExecuteAction::CreateRaw(this, &FCookPak::PakAssetsButtonClicked),
		FCanExecuteAction()
	);

	Extender = MakeShareable(new FExtender);
	Extender->AddToolBarExtension(
		"Settings", 
		EExtensionHook::After, 
		CommandList.ToSharedRef(), 
		FToolBarExtensionDelegate::CreateRaw(this, &FCookPak::AddToolbarExtension)
		);

	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(Extender);
}


void FCookPak::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	UE_LOG(ModuleLog, Log, TEXT("CookPak plugin Ended"));

}


void FCookPak::AddToolbarExtension(FToolBarBuilder& Builder)
{
	UE_LOG(ModuleLog, Log, TEXT("CookPak plugin add extension"));
	
	Builder.AddToolBarButton(FCookPakCommands::Get().UniqueFolderButtonCommand);
	Builder.AddToolBarButton(FCookPakCommands::Get().PakAssetsButtonCommand);
}


void FCookPak::UniqueFolderButtonClicked()
{
	FString Guid = FGuid::NewGuid().ToString();
	bool re = FPlatformFileManager::Get().GetPlatformFile().CreateDirectory((FPaths::GameContentDir() + Guid).GetCharArray().GetData());
}

void FCookPak::PakAssetsButtonClicked()
{
	//Experiment failed: cook assets in one folder
	//FPlatformProcess::CreateProc(*(FPaths::EngineDir() + TEXT("Binaries/Win64/UE4Editor.exe")), *(FPaths::GameDir() + "fhome.uproject -run=cook -targetplatform=WindowsNoEditor"), false, false, false, 0, 0, 0, 0, 0);
	
	// get all directories in the cooked folder
	const FString CookedDir = FPaths::ProjectSavedDir() + "Cooked/WindowsNoEditor/" + FApp::GetGameName() + "/Content/";
	FMyDirectoryVisitor Visitor;
	Visitor.SetParentDirectoryPath(CookedDir);

	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	PlatformFile.IterateDirectory(*CookedDir, Visitor);

	const TArray<FString>& CookedDirectoreis = Visitor.GetDirectoryArray();

	// unreal pak
	const FString EngineDir = FPaths::EngineDir();
	const FString UnrealPakPath = EngineDir / TEXT("Binaries/Win64/UnrealPak.exe");

	// pak cooked assets
	for (int i = 0; i < CookedDirectoreis.Num(); i++)
	{
		const FString PakPath = CookedDir + CookedDirectoreis[i] + "/" + CookedDirectoreis[i] + FString(TEXT(".pak "));
		const FString AssetPath = CookedDir + CookedDirectoreis[i] + "/" + FString(TEXT("*.*"));
		const FString Parameters = PakPath + AssetPath;
		FPlatformProcess::CreateProc(*UnrealPakPath, *Parameters, true, false, false, nullptr, 0, nullptr, nullptr);
	}

	// pak uncooked raw assets
	const FString RawDir = FPaths::GameContentDir();
	for (int i = 0; i < CookedDirectoreis.Num(); i++)
	{
		const FString PakPath = RawDir + CookedDirectoreis[i] + "/" + CookedDirectoreis[i] + FString(TEXT("_raw.pak "));
		const FString AssetPath = RawDir + CookedDirectoreis[i] + "/" + FString(TEXT("*.*"));
		const FString Parameters = PakPath + AssetPath;
		FPlatformProcess::CreateProc(*UnrealPakPath, *Parameters, true, false, false, nullptr, 0, nullptr, nullptr);
	}
}




