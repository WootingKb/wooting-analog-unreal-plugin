#include "WootingAnalogInputFunctionLibrary.h"

bool UWootingAnalogInputFunctionLibrary::IsInitialized() {
	return wooting_analog_is_initialised();
}

float UWootingAnalogInputFunctionLibrary::ReadAnalogKeyID(WootingAnalogResultBlueprint& result, int32 key, int64 device) {

	float readKey = wooting_analog_read_analog_device((uint16_t)key, (WootingAnalog_DeviceID)device);

	if (readKey >= 0.0f) {
		result = WootingAnalogResultBlueprint::Ok;
		return readKey;
	}
	else {
		result = (WootingAnalogResultBlueprint)(int32)readKey;
	}

	return 0.0f;
}

UWootingAnalogInputSDK::UWootingAnalogInputSDK() {
}

UWootingAnalogInputSDK* UWootingAnalogInputFunctionLibrary::GetSDK() {
	return GetMutableDefault<UWootingAnalogInputSDK>();
}
/*float UWootingAnalogInputFunctionLibrary::ReadAnalogKey(WootingAnalogResultBlueprint& result, AnalogVirtualKeysBlueprint key, int64 device) {
	return ReadAnalogKeyID(result, (int32)key, device);
}*/


#define ANALOG_DEVICEBUFFERLEN 10
TArray<FWootingAnalogInputDeviceInfo> UWootingAnalogInputFunctionLibrary::GetConnectedDevices(WootingAnalogResultBlueprint& result) {
	TArray<FWootingAnalogInputDeviceInfo> Devices;
	WootingAnalog_DeviceInfo* deviceInfos[ANALOG_DEVICEBUFFERLEN];


	int res = wooting_analog_get_connected_devices_info(deviceInfos, ANALOG_DEVICEBUFFERLEN);
	if (res >= 0) {
		for (int i = 0; i < res; i++) {
			Devices.Add(FWootingAnalogInputDeviceInfo(deviceInfos[i]));
		}
		result = WootingAnalogResultBlueprint::Ok;
	}
	else if (res < 0) {
		result = (WootingAnalogResultBlueprint)res;
	}

	return Devices;
}
