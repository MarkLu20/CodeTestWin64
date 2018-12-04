// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System;
using System.IO;

public class BreakpointResume : ModuleRules
{
    public BreakpointResume(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicIncludePaths.AddRange(
            new string[] {
                "BreakpointResume/Public",
                
				// ... add public include paths required here ...
			}
            );


        PrivateIncludePaths.AddRange(
            new string[] {

               "BreakpointResume/Private",
               
				// ... add other private include paths required here ...
			}
            );


        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core"
               
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
                "HTTP",
              
				// ... add private dependencies that you statically link with here ...	
			}
            );


        DynamicallyLoadedModuleNames.AddRange(
            new string[]
            {
				// ... add any modules that your module loads dynamically here ...
			}
            );
        if (Target.Type == TargetType.Editor)
        {
            PrivateDependencyModuleNames.AddRange(
            new string[]
            {
               "UnrealEd"
              
				// ... add private dependencies that you statically link with here ...	
			}
            );
            Console.WriteLine("***********************************Have UnrealEd");
            Definitions.AddRange(new string[] { "UE_EDITOR=1" });
        }
        else
        {
            Console.WriteLine("***********************************No UnrealEd");
            Definitions.AddRange(new string[] { "UE_EDITOR=0" });
        }
        //bEnableExceptions = true;
        //bCompileWithClang = true;
    }

}
