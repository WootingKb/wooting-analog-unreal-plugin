// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "WootingAnalogInputDevice.h"
#include "IInputInterface.h"

#define LOCTEXT_NAMESPACE "WootingAnalogInputDevice"



FWootingAnalogInputDevice::FWootingAnalogInputDevice(const TSharedRef<FGenericApplicationMessageHandler>& InMessageHandler) :
MessageHandler(InMessageHandler)
{
	// Initiate your device here
	
	AnalogKeys::InitKeys();
}


FWootingAnalogInputDevice::~FWootingAnalogInputDevice()
{
	// Close your device here
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
		//We want to report the error to the log, but only if it's different than the last result, so we dob't spam the log
		if (result != last_read_buffer_result) {
			last_read_buffer_result = result;
			switch (result) {
				case WootingAnalogResult::WootingAnalogResult_NoDevices:
					UE_LOG(LogWootingAnalogInputDevice, Error, TEXT("No Analog devices connected"));
					return;
				case WootingAnalogResult::WootingAnalogResult_UnInitialized:
					UE_LOG(LogWootingAnalogInputDevice, Error, TEXT("Wooting Analog SDK hasn't been initialised"));
					return;
				default:
					UE_LOG(LogWootingAnalogInputDevice, Error, TEXT("Unhandled Error while reading full buffer %d"), ret);
					return;
			}
		}
	}

	for (int i = 0; i < ret; i++) {
		AnalogVirtualKeys code = (AnalogVirtualKeys)code_buffer[i];
		float analog = analog_buffer[i];

		auto search = AnalogKeys::KeyMap.find(code);
		if (search != AnalogKeys::KeyMap.end()) {
			MessageHandler->OnControllerAnalog(search->second.GetFName(), 0, analog);
			//Remove this key from the active keys, as it has been updated
			active_keys.erase(code);
		}
		else {
			UE_LOG(LogWootingAnalogInputDevice, Warning, TEXT("Couldn't map the (%d) key from the Analog Buffer"), code);
		}
	}

	//Go through the active keys set and set all to zero, as any remainder ones that haven't been erased before means that they were added last frame due to being pressed but are no longer being pressed
	//As the SDK currently only reports the keys when they are pressed, not when let go
	for (std::hash_set<AnalogVirtualKeys>::iterator pIter = active_keys.begin(); pIter != active_keys.end(); pIter++) {
		auto search = AnalogKeys::KeyMap.find(*pIter);
		if (search != AnalogKeys::KeyMap.end()) {
			MessageHandler->OnControllerAnalog(search->second.GetFName(), 0, 0.0f);
		}
	}
	active_keys.clear();

	//Add all the pressed keys from this read to the active keys set
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