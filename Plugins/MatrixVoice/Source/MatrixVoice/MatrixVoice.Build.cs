using UnrealBuildTool;
using System.IO;
using System;


public class MatrixVoice : ModuleRules
{

	public MatrixVoice(ReadOnlyTargetRules Target) : base(Target)

    {
        
        string GVoiceLibPath = string.Empty;

        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicIncludePaths.AddRange(
            new string[] {
                "MatrixVoice/Public",
           
				// ... add public include paths required here ...
			}
            );


        PrivateIncludePaths.AddRange(
            new string[] {
                "MatrixVoice/Private",
				// ... add other private include paths required here ...
			}
            );


        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "Json",
                "JsonUtilities",
                "Projects"
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


        DynamicallyLoadedModuleNames.AddRange(
            new string[]
            {
				// ... add any modules that your module loads dynamically here ...
			}
            );


        //string PluginPath = Utils.MakePathRelativeTo(ModuleDirectory, Target.RelativeEnginePath);
        string PluginPath = Path.Combine(ModuleDirectory);
        System.Console.WriteLine("______________" + PluginPath);
        string GVoiceThirdPartyDir = Path.GetFullPath(Path.Combine(ModuleDirectory, "./ThirdParty/GVoiceSDKLibrary"));

        System.Console.WriteLine("-------------- PluginPath = " + PluginPath);

        //if (Target.Platform == UnrealTargetPlatform.Android)
        //{
        //    PrivateDependencyModuleNames.AddRange(new string[] { "Launch" });

        //    string aplPath = Path.Combine(PluginPath, "GVoiceSDK_APL.xml");
        //    System.Console.WriteLine("-------------- AplPath = " + aplPath);
        //    AdditionalPropertiesForReceipt.Add(new ReceiptProperty("AndroidPlugin", aplPath));
        //}
        //else if (Target.Platform == UnrealTargetPlatform.IOS)
        //{

        //    PrivateIncludePaths.Add("GVoiceSDK/Private/IOS");
        //    PublicIncludePaths.AddRange(new string[] { "Runtime/ApplicationCore/Public/Apple", "Runtime/ApplicationCore/Public/IOS" });


        //    PrivateDependencyModuleNames.AddRange(
        //        new string[]{"ApplicationCore"
        //        // ... add private dependencies that you statically link with here ...
        //        }
        //        );
        /*
        BuildVersion Version;
        if(BuildVersion.TryRead(out Version))
        {
            System.Console.WriteLine("-------------- version = " + Version.MajorVersion +"."+Version.MinorVersion);
            if(Version.MajorVersion > 4 || (Version.MajorVersion == 4 && Version.MinorVersion >= 18))
            {
                PrivateDependencyModuleNames.AddRange(
                new string[]{"ApplicationCore"
                 ... add private dependencies that you statically link with here ...
                }
                );
            }
        }
        */
        //}
        //else if (Target.Platform == UnrealTargetPlatform.Mac)
        //{
        //    Definitions.Add("__GVOICE_MAC__");
        //}

        if (Target.Platform == UnrealTargetPlatform.Win32 || Target.Platform == UnrealTargetPlatform.Win64)
        {
            

            string OSVersion = (Target.Platform == UnrealTargetPlatform.Win32) ? "x86" : "x64";
            PrivateIncludePaths.Add(Path.Combine(GVoiceThirdPartyDir,OSVersion, "include"));
            string libDir = Path.Combine( OSVersion,"lib");
            GVoiceLibPath = Path.Combine(GVoiceThirdPartyDir,libDir);
            PublicLibraryPaths.Add(GVoiceLibPath);
            Console.WriteLine("GVoiceLibPath:" + GVoiceLibPath);

           
           
           
            
            PublicAdditionalLibraries.Add("GCloudVoice.lib");

            
            PublicDelayLoadDLLs.Add("GCloudVoice.dll");
           

            RuntimeDependencies.Add(new RuntimeDependency(Path.Combine(GVoiceLibPath, "GCloudVoice.dll")));

            string binariesDir = Path.Combine(ModuleDirectory, "../../Binaries", Target.Platform.ToString());
            string projectBinaries = Path.Combine(ModuleDirectory, "../../../../Binaries", Target.Platform.ToString());
            //string filename = Path.GetFileName(Filepath);
            string dllPath = Path.Combine(GVoiceLibPath, "GCloudVoice.dll");
            System.Console.WriteLine("src dll=" + dllPath + " dst dir=" + binariesDir);
            if (!Directory.Exists(binariesDir))
                Directory.CreateDirectory(binariesDir);
            if (!Directory.Exists(projectBinaries)) {
                Directory.CreateDirectory(projectBinaries);
            }
            try {
                File.Copy(dllPath, Path.Combine(binariesDir, "GCloudVoice.dll"), true);
                File.Copy(dllPath, Path.Combine(projectBinaries, "GCloudVoice.dll"), true);
                System.Console.WriteLine("pluginBinaries" + binariesDir + "----" + projectBinaries);
            }
            catch (Exception e) {
                System.Console.WriteLine("copy VoiceChatdll exception,maybe have exists,err=", e.ToString());
            }
        }
        else if (Target.Platform == UnrealTargetPlatform.Android)
        {
            string ArchDir = "armeabi-v7a";
            //BASE
            string libDir = ("Android/GCloudVoice/libs");
            GVoiceLibPath = Path.Combine(Path.Combine(GVoiceThirdPartyDir, libDir), ArchDir);
            System.Console.WriteLine("--------------Android GCloudLibPath = " + GVoiceLibPath);
            PublicLibraryPaths.Add(GVoiceLibPath);
            //AddGVoiceLib(Target, "GCloudVoice");
            //AddGCloudLib(Target, "TDataMaster");
            //AddGCloudLib(Target, "gcloud");

            //File srcFile = new File();

            // cz

        }
        //else if (Target.Platform == UnrealTargetPlatform.Mac)
        //{
        //    GVoiceLibPath = GVoiceThirdPartyDir;//
        //    string strLib = GVoiceLibPath + "/Mac/libGCloudVoice.a";
        //    PublicAdditionalLibraries.Add(strLib);

        //}
        //else if (Target.Platform == UnrealTargetPlatform.IOS)
        //{
        //    GVoiceLibPath = GVoiceThirdPartyDir;
        //    Path.Combine(GVoiceLibPath, "iOS/");
        //    string strLib = GVoiceLibPath + "/iOS/libGCloudVoice.a";
        //    PublicAdditionalLibraries.Add(strLib);
        //    string strBundle = GVoiceLibPath + "/iOS/GCloudVoice.bundle";

        //    AdditionalBundleResources.Add(new UEBuildBundleResource("../ThirdParty/GVoiceSDKLibrary/iOS/GCloudVoice.bundle", bInShouldLog: false));

        //    System.Console.WriteLine("---framework path:" + Path.Combine(GVoiceLibPath, "VoiceFrameWork.embeddedframework.zip"));

        //    //PublicAdditionalFrameworks.Add(new UEBuildFramework("VoiceFWForBundle", "../ThirdParty/GVoiceSDKLibrary/iOS/VoiceFWForBundle.embeddedframework.zip", "iOS/GCloudVoice.bundle"));



        //    PublicAdditionalLibraries.AddRange(
        //    new string[] {
        //        "stdc++.6.0.9",
        //        //"libstdc++.6.0.9.tbd","libz.tbd","libc++.tbd","libz.1.1.3.tbd","libsqlite3.tbd","libxml2.tbd",
        //        //Path.Combine(GVoiceThirdPartyDir, "libAPMidasInterface.a")
        //    });


        //    // These are iOS system libraries that Facebook depends on (FBAudienceNetwork, FBNotifications)
        //    PublicFrameworks.AddRange(
        //    new string[] {
        //        "AVFoundation",
        //        "CoreTelephony",
        //        "Security",
        //        "SystemConfiguration",
        //        "AudioToolbox",
        //        "CoreAudio",
        //        "Foundation",
        //    });
        //    //AddGVoiceLib(Target, "libGCloudVoice.a");



        //    /*
        //    PublicAdditionalFrameworks.Add(new UEBuildFramework("ABase", Path.Combine(GCloudThirdPartyDir, "iOS/ABase.embeddedframework.zip")));
        //    */
        //}

    }



    //private void AddGVoiceLib(ReadOnlyTargetRules Target, string in_libName)
    //{
    //    if (Target.Platform == UnrealTargetPlatform.Android || Target.Platform == UnrealTargetPlatform.Linux || Target.Platform == UnrealTargetPlatform.IOS)
    //    {
    //        PublicAdditionalLibraries.Add(in_libName);
    //    }
    //    else if (Target.Platform == UnrealTargetPlatform.Mac)
    //    {
    //    }
    //    else
    //    {
    //        PublicAdditionalLibraries.Add(in_libName + ".lib");
    //    }
    //}
}

