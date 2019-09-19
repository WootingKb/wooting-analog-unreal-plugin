#pragma once
#include "InputCoreTypes.h"
#include <map>

#define LOCTEXT_NAMESPACE "WootingAnalogKeys"


#define VIRTUAL_KEYS \
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
X(Z, 0x5A, "Z") 

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