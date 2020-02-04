// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "WootingAnalogInputDevice.h"
#include "IInputInterface.h"
#include "Framework/Application/SlateApplication.h"
#include "KeyInterceptMessageHandler.h"

#define LOCTEXT_NAMESPACE "WootingAnalogInputDevice"

void DeviceEvent(WootingAnalog_DeviceEventType eventType, WootingAnalog_DeviceInfo_FFI* deviceInfo) {
	UE_LOG(LogWootingAnalogInputDevice, Warning, TEXT("Received Device event"));
	UWootingAnalogInputFunctionLibrary::GetSDK()->OnDeviceEvent.Broadcast((WootingAnalog_DeviceEventTypeBlueprint)eventType, FWootingAnalogInputDeviceInfo(deviceInfo));


	if (eventType == WootingAnalog_DeviceEventType::Connected) {
		UWootingAnalogInputFunctionLibrary::GetSDK()->OnDeviceConnected.Broadcast(FWootingAnalogInputDeviceInfo(deviceInfo));
	}
	else {
		UWootingAnalogInputFunctionLibrary::GetSDK()->OnDeviceDisconnected.Broadcast(FWootingAnalogInputDeviceInfo(deviceInfo));
	}
}

FWootingAnalogInputDevice::FWootingAnalogInputDevice(const TSharedRef<FGenericApplicationMessageHandler>& InMessageHandler) :
MessageHandler(InMessageHandler), InterceptHandler(MakeShareable(new FKeyInterceptMessageHandler(InMessageHandler)))
{
	// Initiate your device here
	
	AnalogKeys::InitKeys();

	wooting_analog_set_device_event_cb(DeviceEvent);

	UE_LOG(LogWootingAnalogInputDevice, Error, TEXT("Set the Key Intercept handler"));
	//TSharedRef<FGenericApplicationMessageHandler> DefaultHandler = FSlateApplication::Get().GetPlatformApplication()->GetMessageHandler();


	FSlateApplication::Get().GetPlatformApplication()->SetMessageHandler(InterceptHandler);
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
				case WootingAnalogResult::NoDevices:
					UE_LOG(LogWootingAnalogInputDevice, Error, TEXT("No Analog devices connected"));
					return;
				case WootingAnalogResult::UnInitialized:
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
#ifdef WITH_EDITOR
			UE_LOG(LogWootingAnalogInputDevice, Warning, TEXT("%d Key has value %f"), code, analog);
#endif
			MessageHandler->OnControllerAnalog(search->second.GetFName(), 0, analog);
		}
		else {
			UE_LOG(LogWootingAnalogInputDevice, Warning, TEXT("Couldn't map the (%d) key from the Analog Buffer"), code);
		}
	}

	std::hash_set<AnalogVirtualKeys> active_keys = {};
	//Add all the pressed keys from this read to the active keys set
	for (int i = 0; i < ret; i++) {
		AnalogVirtualKeys code = (AnalogVirtualKeys)code_buffer[i];
		active_keys.insert(code);
	}

	for (std::hash_set<int32>::iterator pIter = InterceptHandler->PressedKeys.begin(); pIter != InterceptHandler->PressedKeys.end(); pIter++) {
		AnalogVirtualKeys vk = (AnalogVirtualKeys)*pIter;

		//Check if the pressed key is in the active keys list, if not then we want to set it as 1
		if (active_keys.find(vk) == active_keys.end()) {
			UE_LOG(LogWootingAnalogInputDevice, Warning, TEXT("%d Key is pressed but has no analog! Searching for mapping"), *pIter);

			auto search = AnalogKeys::KeyMap.find(vk);
			if (search != AnalogKeys::KeyMap.end()) {
				UE_LOG(LogWootingAnalogInputDevice, Warning, TEXT("%d Key mapping found! Setting it to 1.0f"), *pIter);
				MessageHandler->OnControllerAnalog(search->second.GetFName(), 0, 1.0f);
			}
		}
	}

	for (std::hash_set<int32>::iterator pIter = InterceptHandler->ReleasedKeys.begin(); pIter != InterceptHandler->ReleasedKeys.end(); pIter++) {
		AnalogVirtualKeys vk = (AnalogVirtualKeys)*pIter;

		//Check if the pressed key is in the active keys list, if not then we want to set it as 1
		if (active_keys.find(vk) == active_keys.end()) {
			UE_LOG(LogWootingAnalogInputDevice, Warning, TEXT("%d Key was released but has no analog! Searching for mapping"), *pIter);

			auto search = AnalogKeys::KeyMap.find(vk);
			if (search != AnalogKeys::KeyMap.end()) {
				UE_LOG(LogWootingAnalogInputDevice, Warning, TEXT("%d Key mapping found! Setting it to 0.0f"), *pIter);
				MessageHandler->OnControllerAnalog(search->second.GetFName(), 0, 0.0f);
			}
		}
	}

	InterceptHandler->ReleasedKeys.clear();
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