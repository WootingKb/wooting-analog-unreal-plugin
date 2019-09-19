// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "WootingAnalogInput.h"
#include "Core.h"
#include "Modules/ModuleManager.h"
#include "Interfaces/IPluginManager.h"
#include "../../ThirdParty/WootingAnalogSDK/headers/wooting-analog-wrapper.h"

#define LOCTEXT_NAMESPACE "FWootingAnalogInputModule"

void FWootingAnalogInputModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	// Get the base directory of this plugin
	FString BaseDir = IPluginManager::Get().FindPlugin("WootingAnalogInput")->GetBaseDir();

	// Add on the relative location of the third party dll and load it
	FString LibraryPath;
#if PLATFORM_WINDOWS
	LibraryPath = FPaths::Combine(*BaseDir, TEXT("Source/ThirdParty/WootingAnalogSDK/bin/win64/wooting_analog_wrapper.dll"));
#elif PLATFORM_LINUX
	LibraryPath = FPaths::Combine(*BaseDir, TEXT("Source/ThirdParty/WootingAnalogSDK/bin/linux64/libwooting_analog_wrapper.so"));
#elif PLATFORM_MAC
    LibraryPath = FPaths::Combine(*BaseDir, TEXT("Source/ThirdParty/WootingAnalogSDK/bin/osx64/libwooting_analog_wrapper.dylib"));
#endif // PLATFORM_WINDOWS

	/*ExampleLibraryHandle = !LibraryPath.IsEmpty() ? FPlatformProcess::GetDllHandle(*LibraryPath) : nullptr;

	if (ExampleLibraryHandle)
	{
		// Call the test function in the third party library that opens a message box
		ExampleLibraryFunction();
	}
	else
	{
		FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT("ThirdPartyLibraryError", "Failed to load example third party library"));
	}*/
}

void FWootingAnalogInputModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	// Free the dll handle
	//FPlatformProcess::FreeDllHandle(ExampleLibraryHandle);
	ExampleLibraryHandle = nullptr;
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FWootingAnalogInputModule, WootingAnalogInput)
