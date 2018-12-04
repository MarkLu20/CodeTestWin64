// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System;
using System.IO;

public class AgoraSignal : ModuleRules
{

    private string AgoraLibrary
    {
        get { return Path.GetFullPath(Path.Combine(ModuleDirectory, "./ThirdParty/AgoraLibrary/")); }
    }
    public AgoraSignal(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicIncludePaths.AddRange(
            new string[] {
                "AgoraSignal/Public"
				// ... add public include paths required here ...
			}
            );


        PrivateIncludePaths.AddRange(
            new string[] {
                "AgoraSignal/Private",
				// ... add other private include paths required here ...
			}
            );


        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "Networking",
                "Sockets",
                "Json",
                "JsonUtilities"
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
                //"OnlineSubsystem",
				// ... add private dependencies that you statically link with here ...	
			}
            );


        DynamicallyLoadedModuleNames.AddRange(
            new string[]
            {
				// ... add any modules that your module loads dynamically here ...
			}
            );
      
        if (Target.Platform == UnrealTargetPlatform.Win32 || Target.Platform == UnrealTargetPlatform.Win64) 
            {
            string OSVersion = (Target.Platform == UnrealTargetPlatform.Win32) ? "x86" : "x64";
            PublicIncludePaths.Add(Path.Combine(AgoraLibrary, OSVersion, "include"));
            string LibPath = Path.Combine(AgoraLibrary, OSVersion, "lib");
            System.Console.WriteLine("LibPath------" + LibPath);
            string DllPath = Path.Combine(AgoraLibrary, OSVersion, "dll");
            System.Console.WriteLine("DllPth ----" + DllPath);
            PublicLibraryPaths.Add(LibPath);
            PublicAdditionalLibraries.Add("agora_sig_sdk.lib");
            PublicDelayLoadDLLs.Add(Path.Combine(DllPath, "agora_sig_sdk.dll"));
            RuntimeDependencies.Add(new RuntimeDependency(Path.Combine(DllPath, "agora_sig_sdk.dll")));
            string binariesDir = Path.Combine(ModuleDirectory, "../../Binaries", Target.Platform.ToString());
            string projectBinaries = Path.Combine(ModuleDirectory, "../../../../Binaries", Target.Platform.ToString());
            if (!Directory.Exists(binariesDir)) 
            {
                Directory.CreateDirectory(binariesDir);

            }
            if (!Directory.Exists(projectBinaries)) 
            {
                Directory.CreateDirectory(projectBinaries);

            }
            try {
                string dll = Path.Combine(DllPath, "agora_sig_sdk.dll");
                File.Copy(Path.Combine(DllPath, "agora_sig_sdk.dll"), Path.Combine(projectBinaries, "agora_sig_sdk.dll"));
                File.Copy(Path.Combine(DllPath, "agora_sig_sdk.dll"),Path.Combine(binariesDir, "agora_sig_sdk.dll"));
             
             

            }
            catch (Exception  e) {

                System.Console.WriteLine("copy TextChatdll exception,maybe have exists,err=", e.ToString());
            }
        }

    }


}
