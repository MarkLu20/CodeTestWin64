// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "AliMessage.h"

/*USE THIS CODE IF DEVELOPING A PLUGIN*/

#define LOCTEXT_NAMESPACE "FAliMessageModule"

void FAliMessageModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
}

void FAliMessageModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FAliMessageModule, AliMessage)

/*USE THIS CODE IF DEVELOPING A GAME MODULE*/

//#include "Modules/ModuleManager.h"
//
//IMPLEMENT_PRIMARY_GAME_MODULE(FDefaultGameModuleImpl, AliMessage, "AliMessage");