#pragma once
#include "InputCoreTypes.h"
#include <map>

#define LOCTEXT_NAMESPACE "WootingAnalogKeys"

//X(HANGUL, 0x15, "IME Hangul") \
//X(Separator, 0x6C, "Numpad /") \

#define VIRTUAL_KEYS \
X(BackSpace, 0x08, "Backspace") \
X(Tab, 0x09, "Tab") \
X(Return, 0x0D, "Enter") \
X(Pause, 0x13, "Pause") \
X(CapsLock, 0x14, "Caps Lock") \
X(Escape, 0x1B, "Escape") \
X(Space, 0x20, "Space") \
X(PageUp, 0x21, "Page Up") \
X(PageDown, 0x22, "Page Down") \
X(End, 0x23, "End") \
X(Home, 0x24, "Home") \
X(Left, 0x25, "Left") \
X(Up, 0x26, "Up") \
X(Right, 0x27, "Right") \
X(Down, 0x28, "Down") \
X(PrintScreen, 0x2C, "Print Screen") \
X(Insert, 0x2D, "Insert") \
X(Delete, 0x2E, "Delete") \
X(D0, 0x30, "0") \
X(D1, 0x31, "1") \
X(D2, 0x32, "2") \
X(D3, 0x33, "3") \
X(D4, 0x34, "4") \
X(D5, 0x35, "5") \
X(D6, 0x36, "6") \
X(D7, 0x37, "7") \
X(D8, 0x38, "8") \
X(D9, 0x39, "9") \
X(A, 0x41, "A") \
X(B, 0x42, "B") \
X(C, 0x43, "C") \
X(D, 0x44, "D") \
X(E, 0x45, "E") \
X(F, 0x46, "F") \
X(G, 0x47, "G") \
X(H, 0x48, "H") \
X(I, 0x49, "I") \
X(J, 0x4A, "J") \
X(K, 0x4B, "K") \
X(L, 0x4C, "L") \
X(M, 0x4D, "M") \
X(N, 0x4E, "N") \
X(O, 0x4F, "O") \
X(P, 0x50, "P") \
X(Q, 0x51, "Q") \
X(R, 0x52, "R") \
X(S, 0x53, "S") \
X(T, 0x54, "T") \
X(U, 0x55, "U") \
X(V, 0x56, "V") \
X(W, 0x57, "W") \
X(X, 0x58, "X") \
X(Y, 0x59, "Y") \
X(Z, 0x5A, "Z") \
X(LeftWin, 0x5B, "Left Win") \
X(RightWin, 0x5C, "Right Win") \
X(Num0, 0x60, "Numpad 0") \
X(Num1, 0x61, "Numpad 1") \
X(Num2, 0x62, "Numpad 2") \
X(Num3, 0x63, "Numpad 3") \
X(Num4, 0x64, "Numpad 4") \
X(Num5, 0x65, "Numpad 5") \
X(Num6, 0x66, "Numpad 6") \
X(Num7, 0x67, "Numpad 7") \
X(Num8, 0x68, "Numpad 8") \
X(Num9, 0x69, "Numpad 9") \
X(Multiply, 0x6A, "Numpad *") \
X(Add, 0x6B, "Numpad +") \
X(Subtract, 0x6D, "Numpad -") \
X(Decimal, 0x6E, "Numpad .") \
X(Divide, 0x6F, "Numpad /") \
X(F1, 0x70, "F1") \
X(F2, 0x71, "F2") \
X(F3, 0x72, "F3") \
X(F4, 0x73, "F4") \
X(F5, 0x74, "F5") \
X(F6, 0x75, "F6") \
X(F7, 0x76, "F7") \
X(F8, 0x77, "F8") \
X(F9, 0x78, "F9") \
X(F10, 0x79, "F10") \
X(F11, 0x7A, "F11") \
X(F12, 0x7B, "F12") \
X(F13, 0x7C, "F13") \
X(F14, 0x7D, "F14") \
X(F15, 0x7E, "F15") \
X(F16, 0x7F, "F16") \
X(F17, 0x80, "F17") \
X(F18, 0x81, "F18") \
X(F19, 0x82, "F19") \
X(F20, 0x83, "F20") \
X(F21, 0x84, "F21") \
X(F22, 0x85, "F22") \
X(F23, 0x86, "F23") \
X(F24, 0x87, "F24") \
X(NumLock, 0x90, "Num Lock") \
X(ScrollLock, 0x91, "Scroll Lock") \
X(LeftShift, 0xA0, "Left Shift") \
X(RightShift, 0xA1, "Right Shift") \
X(LeftControl, 0xA2, "Left Control") \
X(RightControl, 0xA3, "Right Control") \
X(LeftMenu, 0xA4, "Left Menu") \
X(RightMenu, 0xA5, "Right Menu") \
X(Oem1, 0xBA, "Oem1 (US ;: key)") \
X(OemPlus, 0xBB, "OemPlus (US + key)") \
X(OemComma, 0xBC, "OemComma (US , key)") \
X(OemMinus, 0xBD, "OemMinus (US - key)") \
X(OemPeriod, 0xBE, "OemPeriod (US . key)") \
X(Oem2, 0xBF, "Oem2 (US /? key)") \
X(Oem3, 0xC0, "Oem3 (US ~ key)") \
X(Oem4, 0xDB, "Oem4 (US [{ key)") \
X(Oem5, 0xDC, "Oem5 (US \\| key)") \
X(Oem6, 0xDD, "Oem6 (US ]} key)") \
X(Oem7, 0xDE, "Oem7 (US '\" key)") \
X(Oem8, 0xDF, "Oem8 (UK # key)") \
X(Fn, 0x301, "Fn Key") \
//X(Oem102, 0xE2, "Oem102 (US > key)") \

#define X(id, code, name) id = code,
enum AnalogVirtualKeys : unsigned short
{
	VIRTUAL_KEYS
};
#undef X

namespace AnalogKeys
{
#define X(id, code, name) const FKey WootingAnalog_ ## id("WootingAnalog_" # id);
	VIRTUAL_KEYS
#undef X
	std::map<AnalogVirtualKeys, FKey> KeyMap = {
#define X(id, code, name) {(AnalogVirtualKeys)code, WootingAnalog_ ## id},
		VIRTUAL_KEYS
#undef X
	};

	const FName categoryName = FName("WootingAnalog");
	void InitKeys() {
		EKeys::AddMenuCategoryDisplayInfo(categoryName, LOCTEXT("WootingAnalogSubCategory", "Analog Keyboard"), TEXT("GraphEditor.KeyEvent_16x"));

#define X(id, code, name) EKeys::AddKey(FKeyDetails(WootingAnalog_ ## id, LOCTEXT("WootingAnalog_" # id, "Analog " ## name), FKeyDetails::FloatAxis, categoryName));
		VIRTUAL_KEYS
#undef X
	}
}
#undef LOCTEXT_NAMESPACE