// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "WootingAnalogInputDeviceModulePrivatePCH.h"
#include "WootingAnalogInputDevice.h"


class FWootingAnalogInputDeviceModule : public IWootingAnalogInputDeviceModule
{
	/** Implements the rest of the IInputDeviceModule interface **/

	/** Creates a new instance of the IInputDevice associated with this IInputDeviceModule **/
	virtual TSharedPtr<class IInputDevice> CreateInputDevice(const TSharedRef<FGenericApplicationMessageHandler>& InMessageHandler);

	/** Called right after the module DLL has been loaded and the module object has been created **/
	virtual void StartupModule() override;

	/** Called before the module is unloaded, right before the module object is destroyed. **/
	virtual void ShutdownModule() override;
};



TSharedPtr<class IInputDevice> FWootingAnalogInputDeviceModule::CreateInputDevice(const TSharedRef<FGenericApplicationMessageHandler>& InMessageHandler)
{
	UE_LOG(LogWootingAnalogInputDevice, Warning, TEXT("Created new input device!"));

	// See GenericInputDevice.h for the definition of the IInputDevice we are returning here
	return MakeShareable(new FWootingAnalogInputDevice(InMessageHandler));
}


void FWootingAnalogInputDeviceModule::StartupModule()
{
	// This code will execute after your module is loaded into memory (but after global variables are initialized, of course.)
	// Custom module-specific init can go here.

	UE_LOG(LogWootingAnalogInputDevice, Display, TEXT("WootingAnalogInputDevicePlugin initiated!"));

	int result = wooting_analog_initialise();
	if (result >= 0) {
		UE_LOG(LogWootingAnalogInputDevice, Display, TEXT("Wooting Analog SDK was successfully initialised and '%d' devices are connected!"), result);

	}
	else {
		switch ((WootingAnalogResult)result) {
		case WootingAnalogResult::IncompatibleVersion:
			UE_LOG(LogWootingAnalogInputDevice, Error, TEXT("Wooting Analog SDK is running an Incompatible Version!"));
			break;
		case WootingAnalogResult::FunctionNotFound:
			UE_LOG(LogWootingAnalogInputDevice, Error, TEXT("Wooting Analog SDK is either not installed or could not be found!"));
			break;
		case WootingAnalogResult::NoPlugins:
			UE_LOG(LogWootingAnalogInputDevice, Error, TEXT("Wooting Analog SDK was found, but it couldn't find any Analog Device plugins!"));
			break;
		default:
			UE_LOG(LogWootingAnalogInputDevice, Warning, TEXT("SDK has been init with result %d"), result);
			break;
		}
	}

	wooting_analog_set_keycode_mode(WootingAnalog_KeycodeType::VirtualKeyTranslate);


	// IMPORTANT: This line registers our input device module with the engine.
	//	      If we do not register the input device module with the engine,
	//	      the engine won't know about our existence. Which means 
	//	      CreateInputDevice never gets called, which means the engine
	//	      will never try to poll for events from our custom input device.
	IModularFeatures::Get().RegisterModularFeature(IInputDeviceModule::GetModularFeatureName(), this);
}


void FWootingAnalogInputDeviceModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UE_LOG(LogWootingAnalogInputDevice, Display, TEXT("WootingAnalogInputDevicePlugin shut down!"));
	wooting_analog_uninitialise();

	// Unregister our input device moduleDisplay
	IModularFeatures::Get().UnregisterModularFeature(IInputDeviceModule::GetModularFeatureName(), this);
}

IMPLEMENT_MODULE(FWootingAnalogInputDeviceModule, WootingAnalogInputDevice)
