// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "MXSqlite.h"

#define LOCTEXT_NAMESPACE "FMXSqliteModule"

void FMXSqliteModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FMXSqliteModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}


void FMXSqliteModule::TestDDS()
{

}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FMXSqliteModule, MXSqlite)