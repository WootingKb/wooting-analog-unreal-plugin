#include "KeyInterceptMessageHandler.h"

/*FKeyInterceptMessageHandler::FKeyInterceptMessageHandler()
{
}*/

FKeyInterceptMessageHandler::FKeyInterceptMessageHandler(const TSharedPtr<FGenericApplicationMessageHandler>& InTargetHandler)
	: TargetHandler(InTargetHandler)
{

}

FKeyInterceptMessageHandler::~FKeyInterceptMessageHandler()
{
}

void FKeyInterceptMessageHandler::SetTargetHandler(const TSharedPtr<FGenericApplicationMessageHandler>& InTargetHandler)
{
	TargetHandler = InTargetHandler;
}

const TSharedPtr<FGenericApplicationMessageHandler> FKeyInterceptMessageHandler::GetTargetHandler() const
{
	return TargetHandler;
}


bool FKeyInterceptMessageHandler::ShouldProcessUserInputMessages(const TSharedPtr< FGenericWindow >& PlatformWindow) const
{
	if (TargetHandler.IsValid())
	{
		return TargetHandler->ShouldProcessUserInputMessages(PlatformWindow);
	}

	return false;
}

bool FKeyInterceptMessageHandler::OnKeyChar(const TCHAR Character, const bool IsRepeat)
{
	if (TargetHandler.IsValid())
	{
		return TargetHandler->OnKeyChar(Character, IsRepeat);
	}

	return false;
}

bool FKeyInterceptMessageHandler::OnKeyDown(const int32 KeyCode, const uint32 CharacterCode, const bool IsRepeat)
{
	UE_LOG(LogTemp, Warning, TEXT("Recieved key down %d %d"), KeyCode, CharacterCode);
	PressedKeys.insert(KeyCode);


	if (TargetHandler.IsValid())
	{
		return TargetHandler->OnKeyDown(KeyCode, CharacterCode, IsRepeat);
	}

	return false;
}

bool FKeyInterceptMessageHandler::OnKeyUp(const int32 KeyCode, const uint32 CharacterCode, const bool IsRepeat)
{
	PressedKeys.erase(KeyCode);
	if (TargetHandler.IsValid())
	{
		return TargetHandler->OnKeyUp(KeyCode, CharacterCode, IsRepeat);
	}

	return false;
}

bool FKeyInterceptMessageHandler::OnMouseDown(const TSharedPtr< FGenericWindow >& Window, const EMouseButtons::Type Button)
{
	if (TargetHandler.IsValid())
	{
		return TargetHandler->OnMouseDown(Window, Button);
	}

	return false;
}

bool FKeyInterceptMessageHandler::OnMouseDown(const TSharedPtr< FGenericWindow >& Window, const EMouseButtons::Type Button, const FVector2D CursorPos)
{
	if (TargetHandler.IsValid())
	{
		return TargetHandler->OnMouseDown(Window, Button, CursorPos);
	}

	return false;
}

bool FKeyInterceptMessageHandler::OnMouseUp(const EMouseButtons::Type Button)
{
	if (TargetHandler.IsValid())
	{
		return TargetHandler->OnMouseUp(Button);
	}

	return false;
}

bool FKeyInterceptMessageHandler::OnMouseUp(const EMouseButtons::Type Button, const FVector2D CursorPos)
{
	if (TargetHandler.IsValid())
	{
		return TargetHandler->OnMouseUp(Button, CursorPos);
	}

	return false;
}

bool FKeyInterceptMessageHandler::OnMouseDoubleClick(const TSharedPtr< FGenericWindow >& Window, const EMouseButtons::Type Button)
{
	if (TargetHandler.IsValid())
	{
		return TargetHandler->OnMouseDoubleClick(Window, Button);
	}

	return false;
}

bool FKeyInterceptMessageHandler::OnMouseDoubleClick(const TSharedPtr< FGenericWindow >& Window, const EMouseButtons::Type Button, const FVector2D CursorPos)
{
	if (TargetHandler.IsValid())
	{
		return TargetHandler->OnMouseDoubleClick(Window, Button, CursorPos);
	}

	return false;
}

bool FKeyInterceptMessageHandler::OnMouseWheel(const float Delta)
{
	if (TargetHandler.IsValid())
	{
		return TargetHandler->OnMouseWheel(Delta);
	}

	return false;
}

bool FKeyInterceptMessageHandler::OnMouseWheel(const float Delta, const FVector2D CursorPos)
{
	if (TargetHandler.IsValid())
	{
		return TargetHandler->OnMouseWheel(Delta, CursorPos);
	}

	return false;
}

bool FKeyInterceptMessageHandler::OnMouseMove()
{
	if (TargetHandler.IsValid())
	{
		return TargetHandler->OnMouseMove();
	}

	return false;
}

bool FKeyInterceptMessageHandler::OnRawMouseMove(const int32 X, const int32 Y)
{
	if (TargetHandler.IsValid())
	{
		return TargetHandler->OnRawMouseMove(X,Y);
	}

	return false;
}

bool FKeyInterceptMessageHandler::OnCursorSet()
{
	if (TargetHandler.IsValid())
	{
		return TargetHandler->OnCursorSet();
	}

	return false;
}

bool FKeyInterceptMessageHandler::OnControllerAnalog(FGamepadKeyNames::Type KeyName, int32 ControllerId, float AnalogValue)
{
	if (TargetHandler.IsValid())
	{
		return TargetHandler->OnControllerAnalog(KeyName, ControllerId, AnalogValue);
	}

	return false;
}

bool FKeyInterceptMessageHandler::OnControllerButtonPressed(FGamepadKeyNames::Type KeyName, int32 ControllerId, bool IsRepeat)
{
	if (TargetHandler.IsValid())
	{
		return TargetHandler->OnControllerButtonPressed(KeyName, ControllerId, IsRepeat);
	}

	return false;
}

bool FKeyInterceptMessageHandler::OnControllerButtonReleased(FGamepadKeyNames::Type KeyName, int32 ControllerId, bool IsRepeat)
{
	if (TargetHandler.IsValid())
	{
		return TargetHandler->OnControllerButtonReleased(KeyName, ControllerId, IsRepeat);
	}

	return false;
}

void FKeyInterceptMessageHandler::OnBeginGesture()
{
	if (TargetHandler.IsValid())
	{
		TargetHandler->OnBeginGesture();
	}
}

bool FKeyInterceptMessageHandler::OnTouchGesture(EGestureEvent GestureType, const FVector2D& Delta, float WheelDelta, bool bIsDirectionInvertedFromDevice)
{
	return false;
}

void FKeyInterceptMessageHandler::OnEndGesture()
{
	if (TargetHandler.IsValid())
	{
		TargetHandler->OnEndGesture();
	}
}

bool FKeyInterceptMessageHandler::OnTouchStarted(const TSharedPtr< FGenericWindow >& Window, const FVector2D& Location, float Force, int32 TouchIndex, int32 ControllerId)
{
	if (TargetHandler.IsValid())
	{
		return TargetHandler->OnTouchStarted(Window, Location, Force, TouchIndex, ControllerId);
	}

	return false;
}

bool FKeyInterceptMessageHandler::OnTouchMoved(const FVector2D& Location, float Force, int32 TouchIndex, int32 ControllerId)
{
	if (TargetHandler.IsValid())
	{
		return TargetHandler->OnTouchMoved(Location, Force, TouchIndex, ControllerId);
	}

	return false;
}

bool FKeyInterceptMessageHandler::OnTouchEnded(const FVector2D& Location, int32 TouchIndex, int32 ControllerId)
{
	if (TargetHandler.IsValid())
	{
		return TargetHandler->OnTouchEnded(Location, TouchIndex, ControllerId);
	}

	return false;
}

bool FKeyInterceptMessageHandler::OnTouchForceChanged(const FVector2D& Location, float Force, int32 TouchIndex, int32 ControllerId)
{
	if (TargetHandler.IsValid())
	{
		return TargetHandler->OnTouchForceChanged(Location, Force, TouchIndex, ControllerId);
	}

	return false;
}

bool FKeyInterceptMessageHandler::OnTouchFirstMove(const FVector2D& Location, float Force, int32 TouchIndex, int32 ControllerId)
{
	if (TargetHandler.IsValid())
	{
		return TargetHandler->OnTouchFirstMove(Location, Force, TouchIndex, ControllerId);
	}

	return false;
}

void FKeyInterceptMessageHandler::ShouldSimulateGesture(EGestureEvent Gesture, bool bEnable)
{
	if (TargetHandler.IsValid())
	{
		TargetHandler->ShouldSimulateGesture(Gesture, bEnable);
	}
}

bool FKeyInterceptMessageHandler::OnMotionDetected(const FVector& Tilt, const FVector& RotationRate, const FVector& Gravity, const FVector& Acceleration, int32 ControllerId)
{
	if (TargetHandler.IsValid())
	{
		return TargetHandler->OnMotionDetected(Tilt, RotationRate, Gravity, Acceleration, ControllerId);
	}

	return false;
}

bool FKeyInterceptMessageHandler::OnSizeChanged(const TSharedRef< FGenericWindow >& Window, const int32 Width, const int32 Height, bool bWasMinimized /*= false*/)
{
	if (TargetHandler.IsValid())
	{
		return TargetHandler->OnSizeChanged(Window, Width, Height, bWasMinimized);
	}

	return false;
}

void FKeyInterceptMessageHandler::OnOSPaint(const TSharedRef<FGenericWindow>& Window)
{
	if (TargetHandler.IsValid())
	{
		TargetHandler->OnOSPaint(Window);
	}
}

FWindowSizeLimits FKeyInterceptMessageHandler::GetSizeLimitsForWindow(const TSharedRef<FGenericWindow>& Window) const
{
	if (TargetHandler.IsValid())
	{
		return TargetHandler->GetSizeLimitsForWindow(Window);
	}

	return FWindowSizeLimits();
}

void FKeyInterceptMessageHandler::OnResizingWindow(const TSharedRef< FGenericWindow >& Window)
{
	if (TargetHandler.IsValid())
	{
		TargetHandler->OnResizingWindow(Window);
	}
}

bool FKeyInterceptMessageHandler::BeginReshapingWindow(const TSharedRef< FGenericWindow >& Window)
{
	if (TargetHandler.IsValid())
	{
		return TargetHandler->BeginReshapingWindow(Window);
	}

	return true;
}

void FKeyInterceptMessageHandler::FinishedReshapingWindow(const TSharedRef< FGenericWindow >& Window)
{
	if (TargetHandler.IsValid())
	{
		TargetHandler->FinishedReshapingWindow(Window);
	}
}

void FKeyInterceptMessageHandler::HandleDPIScaleChanged(const TSharedRef< FGenericWindow >& Window)
{
	if (TargetHandler.IsValid())
	{
		return TargetHandler->HandleDPIScaleChanged(Window);
	}
}

void FKeyInterceptMessageHandler::OnMovedWindow(const TSharedRef< FGenericWindow >& Window, const int32 X, const int32 Y)
{
	if (TargetHandler.IsValid())
	{
		return TargetHandler->HandleDPIScaleChanged(Window);
	}
}

bool FKeyInterceptMessageHandler::OnWindowActivationChanged(const TSharedRef< FGenericWindow >& Window, const EWindowActivation ActivationType)
{
	if (TargetHandler.IsValid())
	{
		return TargetHandler->OnWindowActivationChanged(Window, ActivationType);
	}

	return false;
}

bool FKeyInterceptMessageHandler::OnApplicationActivationChanged(const bool IsActive)
{
	if (TargetHandler.IsValid())
	{
		return TargetHandler->OnApplicationActivationChanged(IsActive);
	}

	return false;
}

bool FKeyInterceptMessageHandler::OnConvertibleLaptopModeChanged()
{
	if (TargetHandler.IsValid())
	{
		return TargetHandler->OnConvertibleLaptopModeChanged();
	}

	return false;
}

EWindowZone::Type FKeyInterceptMessageHandler::GetWindowZoneForPoint(const TSharedRef< FGenericWindow >& Window, const int32 X, const int32 Y)
{
	if (TargetHandler.IsValid())
	{
		return TargetHandler->GetWindowZoneForPoint(Window, X, Y);
	}

	return EWindowZone::NotInWindow;
}

void FKeyInterceptMessageHandler::OnWindowClose(const TSharedRef< FGenericWindow >& Window)
{
	if (TargetHandler.IsValid())
	{
		TargetHandler->OnWindowClose(Window);
	}
}

EDropEffect::Type FKeyInterceptMessageHandler::OnDragEnterText(const TSharedRef< FGenericWindow >& Window, const FString& Text)
{
	if (TargetHandler.IsValid())
	{
		return TargetHandler->OnDragEnterText(Window, Text);
	}

	return EDropEffect::None;
}

EDropEffect::Type FKeyInterceptMessageHandler::OnDragEnterFiles(const TSharedRef< FGenericWindow >& Window, const TArray< FString >& Files)
{
	if (TargetHandler.IsValid())
	{
		return TargetHandler->OnDragEnterFiles(Window, Files);
	}

	return EDropEffect::None;
}

EDropEffect::Type FKeyInterceptMessageHandler::OnDragEnterExternal(const TSharedRef< FGenericWindow >& Window, const FString& Text, const TArray< FString >& Files)
{
	if (TargetHandler.IsValid())
	{
		return TargetHandler->OnDragEnterExternal(Window, Text, Files);
	}

	return EDropEffect::None;
}

EDropEffect::Type FKeyInterceptMessageHandler::OnDragOver(const TSharedPtr< FGenericWindow >& Window)
{
	if (TargetHandler.IsValid())
	{
		return TargetHandler->OnDragOver(Window);
	}

	return EDropEffect::None;
}

void FKeyInterceptMessageHandler::OnDragLeave(const TSharedPtr< FGenericWindow >& Window)
{
	if (TargetHandler.IsValid())
	{
		TargetHandler->OnDragLeave(Window);
	}
}

EDropEffect::Type FKeyInterceptMessageHandler::OnDragDrop(const TSharedPtr< FGenericWindow >& Window)
{
	if (TargetHandler.IsValid())
	{
		return TargetHandler->OnDragDrop(Window);
	}

	return EDropEffect::None;
}

bool FKeyInterceptMessageHandler::OnWindowAction(const TSharedRef< FGenericWindow >& Window, const EWindowAction::Type InActionType)
{
	if (TargetHandler.IsValid())
	{
		return TargetHandler->OnWindowAction(Window, InActionType);
	}

	return true;
}