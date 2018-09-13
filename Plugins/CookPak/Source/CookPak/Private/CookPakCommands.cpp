#include "CookPakPrivatePCH.h"
#include "CookPakCommands.h"

#define LOCTEXT_NAMESPACE "CookPak"

void FCookPakCommands::RegisterCommands()
{
	UI_COMMAND(UniqueFolderButtonCommand, "CreateUniqueFolder", "CookPak Plugin: Create a folder with unique name", EUserInterfaceActionType::Button, FInputGesture());
	UI_COMMAND(PakAssetsButtonCommand, "PakAssets", "CookPak Plugin: cook the project and pak assets in each folder", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE