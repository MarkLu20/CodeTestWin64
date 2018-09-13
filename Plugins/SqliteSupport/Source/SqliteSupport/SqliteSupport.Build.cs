// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.IO;

public class SqliteSupport : ModuleRules
{      
    public SqliteSupport(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
        //Type = ModuleType.External;

        PublicIncludePaths.AddRange(
			new string[] {
				"SqliteSupport/Public"
				// ... add public include paths required here ...
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				"SqliteSupport/Private",
                //"SqliteSupport/ThirdParty/SqliteLibrary/x64/include",
              //  "SqliteSupport/ThirdParty/SqliteLibrary/x86/include"
				// ... add other private include paths required here ...
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				// ... add private dependencies that you statically link with here ...	
			}
			);

        LoadSqliteLib(Target);
    }

    private string PluginPath
    {
        get { return ModuleDirectory; }
    }

    private string ThirdPartyPath
    {
        get { return Path.GetFullPath(Path.Combine(PluginPath, "./ThirdParty/SqliteLibrary")); }
    }

    public bool LoadSqliteLib(ReadOnlyTargetRules Target)
    {
        bool isLibrarySupported = false;

        if ((Target.Platform == UnrealTargetPlatform.Win64) || (Target.Platform == UnrealTargetPlatform.Win32))
        {
            isLibrarySupported = true;

            string PlatformString = (Target.Platform == UnrealTargetPlatform.Win64) ? "x64" : "x86";
            //string LibrariesPath = Path.Combine(ThirdPartyPath, "Libs");
            string SqliteLibPath= Path.Combine(ThirdPartyPath, PlatformString);

            PublicIncludePaths.Add(Path.Combine(SqliteLibPath, "lib"));
            PublicAdditionalLibraries.Add(Path.Combine(SqliteLibPath,"lib", "sqlite.lib"));
            PublicIncludePaths.Add(Path.Combine(SqliteLibPath,"include"));
        }

        Definitions.Add(string.Format("WITH_SQLITE3_LIB_BINDING={0}", isLibrarySupported ? 1 : 0));

        return isLibrarySupported;
    }
}
