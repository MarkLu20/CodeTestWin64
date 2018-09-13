using UnrealBuildTool;
using System.Collections.Generic;

[SupportedPlatforms(UnrealPlatformClass.Server)]
public class CodeTestForWindowsServerTarget : TargetRules   // Change this line as shown previously
{
       public CodeTestForWindowsServerTarget(TargetInfo Target) : base(Target)  // Change this line as shown previously
       {
        Type = TargetType.Server;
        ExtraModuleNames.Add("CodeTestForWindows");    // Change this line as shown previously
       }
}