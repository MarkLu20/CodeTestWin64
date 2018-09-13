#pragma once

#include "Commands.h"


class FCookPakCommands : public TCommands<FCookPakCommands>
{
public:
	FCookPakCommands() : TCommands<FCookPakCommands>(TEXT("CookPak"),NSLOCTEXT("Contexts", "CookPak", "CookPak Plugin"), NAME_None, FEditorStyle::GetStyleSetName())
	{
	}

	virtual void RegisterCommands() override;

	TSharedPtr<FUICommandInfo> UniqueFolderButtonCommand;
	TSharedPtr<FUICommandInfo> PakAssetsButtonCommand;
};