// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

/*USE THIS CODE IF DEVELOPING A PLUGIN*/

#include "ModuleManager.h"

class FAliMessageModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

/*USE THIS CODE IF DEVELOPING A GAME MODULE*/

//#include "CoreMinimal.h"