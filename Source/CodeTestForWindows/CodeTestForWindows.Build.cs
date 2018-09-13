// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class CodeTestForWindows : ModuleRules
{
	public CodeTestForWindows(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject",
            "Engine", "InputCore","HTTP","Json", "WebSockets",
            "JsonUtilities","OnlineSubsystem","OnlineSubsystemUtils",
            "MXLoadingScreen" ,"Sockets","NetWorking","UMG", "SqliteSupport",
            "AgoraVoice", "OpenFireChat","AIModule","GameplayTasks",
            "HeadMountedDisplay","AgoraSignal" });


		PrivateDependencyModuleNames.AddRange(new string[] { "Slate","SlateCore", "MXLoadingScreen" });
        DynamicallyLoadedModuleNames.AddRange(new string[] { "OnlineSubsystemNull" });
        Definitions.Add("WITH_WEBSOCKETS=1");


        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");
        DynamicallyLoadedModuleNames.Add("OnlineSubsystemSteam");
        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }
}
