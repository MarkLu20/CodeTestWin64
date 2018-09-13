// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

using System.IO;

namespace UnrealBuildTool.Rules
{
	public class CookPak : ModuleRules
	{
		public CookPak(TargetInfo Target)
		{
            string EnginePath = Path.GetFullPath(BuildConfiguration.RelativeEnginePath);
            string EditorPath = EnginePath + "Source/Editor/";

            PublicIncludePaths.AddRange(
				new string[] {
					// ... add public include paths required here ...
                    "Developer/CookPak/Public",
                }
				);

			PrivateIncludePaths.AddRange(
				new string[] {
                    "Developer/CookPak/Private",
					// ... add other private include paths required here ...
				}
				);
            PrivateIncludePaths.Add(EditorPath + "UnrealEd/Private");

			PublicDependencyModuleNames.AddRange(
				new string[]
				{
					"Core",
                    "CoreUObject",
                    "DesktopPlatform",
                    "Engine",
                    "LevelEditor",
                    "MainFrame",
                    "EditorStyle",
                    "Slate",
                    "SlateCore",
                    "UnrealEd"
					// ... add other public dependencies that you statically link with here ...
				}
				);

			PrivateDependencyModuleNames.AddRange(
				new string[]
				{
					// ... add private dependencies that you statically link with here ...
				}
				);

			DynamicallyLoadedModuleNames.AddRange(
				new string[]
				{
					// ... add any modules that your module loads dynamically here ...
				}
				);
		}
	}
}