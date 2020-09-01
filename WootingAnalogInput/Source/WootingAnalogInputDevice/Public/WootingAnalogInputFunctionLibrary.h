#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Features/IModularFeatures.h"
#include "WootingAnalogInputDeviceModulePrivatePCH.h"
#include "DelegateCombinations.h"
#include "WootingAnalogInputFunctionLibrary.generated.h"

UENUM(BlueprintType)
enum class WootingAnalogResultBlueprint : uint8 {
	Ok = 1 UMETA(DisplayName = "Ok"),

	None = 0 UMETA(DisplayName = "None"),
	/// Item hasn't been initialized
	UnInitialized = 48 UMETA(DisplayName = "UnInitialized"), //48 is -2000 when cast as uint8
	/// No Devices are connected
	NoDevices UMETA(DisplayName = "No Devices"),
	/// Device has been disconnected
	DeviceDisconnected UMETA(DisplayName = "Device Disconnected"),
	/// Generic Failure
	Failure UMETA(DisplayName = "Failure"),
	/// A given parameter was invalid
	InvalidArgument UMETA(DisplayName = "Invalid Argument"),
	/// No Plugins were found
	NoPlugins UMETA(DisplayName = "No Plugins"),
	/// The specified function was not found in the library
	FunctionNotFound UMETA(DisplayName = "Function Not Found"),
	/// No Keycode mapping to HID was found for the given Keycode
	NoMapping UMETA(DisplayName = "No Mapping"),
	/// Indicates that it isn't available on this platform
	NotAvailable UMETA(DisplayName = "Not Available"),
};

UENUM(BlueprintType)
enum class WootingAnalog_DeviceEventTypeBlueprint : uint8 {
	/// Device has been connected
	Connected = 1 UMETA(DisplayName = "Connected"),

	None = 0 UMETA(DisplayName = "Null"),
	/// Device has been disconnected
	Disconnected UMETA(DisplayName = "Disconnected")
};

USTRUCT(BlueprintType)
struct FWootingAnalogInputDeviceInfo
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "WootingAnalogInput")
	int32 VendorID;

	UPROPERTY(BlueprintReadOnly, Category = "WootingAnalogInput")
	int32 ProductID;

	UPROPERTY(BlueprintReadOnly, Category = "WootingAnalogInput")
	FString	ManufacturerName;

	UPROPERTY(BlueprintReadOnly, Category = "WootingAnalogInput")
	FString	DeviceName;

	UPROPERTY(BlueprintReadOnly, Category = "WootingAnalogInput")
	int64 DeviceID;

	FWootingAnalogInputDeviceInfo()
	{
	}

	FWootingAnalogInputDeviceInfo(WootingAnalog_DeviceInfo_FFI* device_info)
	{
		VendorID = device_info->vendor_id;
		ProductID = device_info->product_id;
		ManufacturerName = FString(device_info->manufacturer_name);
		DeviceName = FString(device_info->device_name);
		DeviceID = device_info->device_id;
	}
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDeviceInfoDelegate, FWootingAnalogInputDeviceInfo, Device);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FDeviceEventDelegate, WootingAnalog_DeviceEventTypeBlueprint, EventType, FWootingAnalogInputDeviceInfo, Device);

UCLASS()
class UWootingAnalogInputSDK : public UObject {
	GENERATED_BODY()
private:
	

public:
	UWootingAnalogInputSDK();

	//UFUNCTION(BlueprintImplementableEvent, Category = "WootingAnalogInput")
	//void OnConnected();


	UPROPERTY(BlueprintAssignable, Category = "WootingAnalogInput")
	FDeviceInfoDelegate OnDeviceConnected;

	UPROPERTY(BlueprintAssignable, Category = "WootingAnalogInput")
	FDeviceInfoDelegate OnDeviceDisconnected;

	UPROPERTY(BlueprintAssignable, Category = "WootingAnalogInput")
	FDeviceEventDelegate OnDeviceEvent;
};

/*
 * Wooting Analog Input additional functions
 */
UCLASS()
class UWootingAnalogInputFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
private:

public:
	UFUNCTION(BlueprintPure, Category = "WootingAnalogInput")
	static UWootingAnalogInputSDK* GetSDK();
	/**
	* Get a bool indicating if the Wooting Analog SDK has been initialised
	*/
	UFUNCTION(BlueprintPure, Category = "WootingAnalogInput")
	static bool IsInitialized();

	UFUNCTION(BlueprintCallable, Category = "WootingAnalogInput")
	static float ReadAnalogKeyID(WootingAnalogResultBlueprint& result, int32 key, int64 device = 0);

	//UFUNCTION(BlueprintCallable, Category = "WootingAnalogInput")
	//static float ReadAnalogKey(WootingAnalogResultBlueprint& result, AnalogVirtualKeysBlueprint key, int64 device = 0);

	UFUNCTION(BlueprintPure, Category = "WootingAnalogInput")
	static TArray<FWootingAnalogInputDeviceInfo> GetConnectedDevices(WootingAnalogResultBlueprint& result);
};
