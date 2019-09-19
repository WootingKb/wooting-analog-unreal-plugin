// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "WootingAnalogInputDevice.h"
#include "WootingAnalogInputDeviceModulePrivatePCH.h"
#include "IInputInterface.h"
#include "wooting-analog-wrapper.h"

#define LOCTEXT_NAMESPACE "WootingAnalogInputDevice"
DEFINE_LOG_CATEGORY_STATIC(LogWootingAnalogInputDevice, Log, All);


FWootingAnalogInputDevice::FWootingAnalogInputDevice(const TSharedRef<FGenericApplicationMessageHandler>& InMessageHandler) :
MessageHandler(InMessageHandler)
{
	// Initiate your device here
	WootingAnalogResult result = wooting_analog_initialise();
	UE_LOG(LogWootingAnalogInputDevice, Warning, TEXT("SDK has been init with result %d"), result);
	wooting_analog_set_keycode_mode(WootingAnalog_KeycodeType::WootingAnalog_KeycodeType_VirtualKeyTranslate);
	AnalogKeys::InitKeys();
}


FWootingAnalogInputDevice::~FWootingAnalogInputDevice()
{
	// Close your device here
	wooting_analog_uninitialise();
}


void FWootingAnalogInputDevice::Tick(float DeltaTime)
{
	// Nothing necessary to do (boilerplate code to complete the interface)
}


void FWootingAnalogInputDevice::SendControllerEvents()
{
	// Poll your device here and fire off events related to its current state

	// Example: Sending a dummy value
	//UE_LOG(LogTemp, Warning, TEXT("Sending dummy analog controller event!"));

	
	int ret = wooting_analog_read_full_buffer(code_buffer, analog_buffer, ANALOG_BUFFER_LEN);
	if (ret < 0) {
		WootingAnalogResult result = (WootingAnalogResult)ret;
		switch (result) {
			case WootingAnalogResult::WootingAnalogResult_NoDevices:
				UE_LOG(LogWootingAnalogInputDevice, Error, TEXT("Error: No Analog devices connected"));
				break;
			default:
				UE_LOG(LogWootingAnalogInputDevice, Error, TEXT("Error while reading full buffer %d"), ret);
				return;
		}
	}

	/*if (newval != wkeyval) {
		UE_LOG(LogWootingAnalogInputDevice, Warning, TEXT("W Key has value %f"), newval);
		wkeyval = newval;
	}*/
	for (int i = 0; i < ret; i++) {
		AnalogVirtualKeys code = (AnalogVirtualKeys)code_buffer[i];
		float analog = analog_buffer[i];

		auto search = AnalogKeys::KeyMap.find(code);
		if (search != AnalogKeys::KeyMap.end()) {
			MessageHandler->OnControllerAnalog(search->second.GetFName(), 0, analog);
			active_keys.erase(code);
		}
		else {
			UE_LOG(LogWootingAnalogInputDevice, Warning, TEXT("Couldn't map the (%d) key from the Analog Buffer"), code);
		}
	}

	for (std::hash_set<AnalogVirtualKeys>::iterator pIter = active_keys.begin(); pIter != active_keys.end(); pIter++) {
		auto search = AnalogKeys::KeyMap.find(*pIter);
		if (search != AnalogKeys::KeyMap.end()) {
			MessageHandler->OnControllerAnalog(search->second.GetFName(), 0, 0.0f);
		}
	}
	active_keys.clear();

	for (int i = 0; i < ret; i++) {
		AnalogVirtualKeys code = (AnalogVirtualKeys)code_buffer[i];
		active_keys.insert(code);
	}
}


void FWootingAnalogInputDevice::SetMessageHandler(const TSharedRef< FGenericApplicationMessageHandler >& InMessageHandler)
{
	MessageHandler = InMessageHandler;
}


bool FWootingAnalogInputDevice::Exec(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar)
{
	// Nothing necessary to do (boilerplate code to complete the interface)
	return false;
}


void FWootingAnalogInputDevice::SetChannelValue(int32 ControllerId, FForceFeedbackChannelType ChannelType, float Value)
{
	// Nothing necessary to do (boilerplate code to complete the interface)
}


void FWootingAnalogInputDevice::SetChannelValues(int32 ControllerId, const FForceFeedbackValues &values)
{
	// Nothing necessary to do (boilerplate code to complete the interface)
}

#undef LOCTEXT_NAMESPACE