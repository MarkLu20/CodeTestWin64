// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System;
using System.IO;

public class AgoraVoice : ModuleRules
{  public string AgoraVoiceLibrary
    {

        get { return Path.GetFullPath( Path.Combine(ModuleDirectory, "./ThirdParty/AgroaVoiceLibrary")); }
    }
	public AgoraVoice(ReadOnlyTargetRules Target) : base(Target)
	{
        Console.WriteLine("VoiceLibray"+ AgoraVoiceLibrary);
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(
			new string[] {
				"AgoraVoice/Public"
				// ... add public include paths required here ...
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				"AgoraVoice/Private",
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
                "Json",
                "Json",
                "JsonUtilities",
                "Projects"
				// ... add private dependencies that you statically link with here ...	
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
            );
        if (Target.Platform == UnrealTargetPlatform.Win32 || Target.Platform == UnrealTargetPlatform.Win64) {
            string OSVersion = (Target.Platform == UnrealTargetPlatform.Win32 ? "x86" : "x64");
            PrivateIncludePaths.Add(Path.Combine(AgoraVoiceLibrary, OSVersion, "include"));
            Console.WriteLine("AgoraVoiceLibarary Include" + Path.Combine(AgoraVoiceLibrary,OSVersion ,"include"));
            string DllPath = Path.Combine(AgoraVoiceLibrary,OSVersion, "dll");
            string LibPath = Path.Combine(AgoraVoiceLibrary, OSVersion, "lib");
            PublicLibraryPaths.Add(LibPath);
            PublicAdditionalLibraries.Add(Path.Combine(LibPath, "agora_rtc_sdk.lib"));
            PublicDelayLoadDLLs.Add(Path.Combine(DllPath, "agora_rtc_sdk.dll"));
            RuntimeDependencies.Add(new RuntimeDependency(Path.Combine(DllPath, "agora_rtc_sdk.dll")));
              
              

            // RuntimeDependencies.Add(new RuntimeDependency(Path.Combine(DllPath, "agora_sig_sdk.dll")));
            string BinariesDir = Path.GetFullPath(Path.Combine(ModuleDirectory, "../../Binaries", Target.Platform.ToString()));
            string ProjectBinariesDir = Path.GetFullPath(Path.Combine(ModuleDirectory, "../../../../Binaries", Target.Platform.ToString()));
            Console.WriteLine("AgoraVoiceBinaries" + BinariesDir);
            Console.WriteLine("AgoraVoiceProjectBinaries" + ProjectBinariesDir);

            if (!Directory.Exists(BinariesDir)) {
                Directory.CreateDirectory(BinariesDir);

            }
            if (!Directory.Exists(ProjectBinariesDir)) {
                Directory.CreateDirectory(ProjectBinariesDir);

            }
            try {
                File.Copy(Path.Combine(DllPath, "agora_rtc_sdk.dll"), Path.Combine(ProjectBinariesDir, "agora_rtc_sdk.dll"));
                //File.Copy(Path.Combine(DllPath, "agora_sig_sdk.dll"), Path.Combine(ProjectBinariesDir, "agora_sig_sdk.dll"));
                File.Copy(Path.Combine(DllPath, "agora_rtc_sdk.dll"), Path.Combine(BinariesDir, "agora_rtc_sdk.dll"));
                File.Copy(Path.Combine(DllPath, "agora_sig_sdk.dll"),Path.Combine(BinariesDir, "agora_sig_sdk.dll"));
            }
            catch (Exception e) {

                System.Console.WriteLine("copy AgoraVoicedll exception,maybe have exists,err=", e.ToString());
            }


        }
    }
}
