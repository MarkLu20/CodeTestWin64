using UnrealBuildTool;

// This module must be loaded "PreLoadingScreen" in the .uproject file, otherwise it will not hook in time!

public class MXLoadingScreen : ModuleRules
{
    public MXLoadingScreen(ReadOnlyTargetRules Target) : base(Target)
	{
		//PrivateIncludePaths.Add("../MXLoadingScreen/Private/");
  //      PublicIncludePaths.Add("../MXLoadingScreen/Public/");

        PrivateDependencyModuleNames.AddRange(
			new string[] {
				"Core",
				"CoreUObject",
				"MoviePlayer",
				"Slate",
				"SlateCore",
				"InputCore"
			}
		);
	}
}
