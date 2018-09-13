// Fill out your copyright notice in the Description page of Project Settings.

using System.IO;
using UnrealBuildTool;

public class SqliteLibrary : ModuleRules
{
    public SqliteLibrary(ReadOnlyTargetRules Target) : base(Target)
    {
        Type = ModuleType.External;

        if (Target.Platform == UnrealTargetPlatform.Win64)
        {
            // Add the import library

            //PublicAdditionalLibraries.Add("ExampleLibrary.lib");

            // Delay-load the DLL, so we can load it from the right place first
            //PublicDelayLoadDLLs.Add("ExampleLibrary.dll");
        }
        else if (Target.Platform == UnrealTargetPlatform.Mac)
        {
            //PublicDelayLoadDLLs.Add(Path.Combine(ModuleDirectory, "Mac", "Release", "libExampleLibrary.dylib"));
        }
    }
}
