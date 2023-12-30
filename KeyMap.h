
// VKAlphaView.cpp: Implementierung der CVKAlphaView-Klasse
//
#pragma once

#include <array>
#include <map>

enum class eKeys : int32_t
{
	eKey0 = 0,
	eKey1,
	eKey2,
	eKey3,
	eKey4,
	eKey5,
	eKey6,
	eKey7,
	eKey8,
	eKey9,
	eKeyA,
	eKeyB,
	eKeyC,
	eKeyD,
	eKeyE,
	eKeyF,
	eKeyG,
	eKeyH,
	eKeyI,
	eKeyJ,
	eKeyK,
	eKeyL,
	eKeyM,
	eKeyN,
	eKeyO,
	eKeyP,
	eKeyQ,
	eKeyR,
	eKeyS,
	eKeyT,
	eKeyU,
	eKeyV,
	eKeyW,
	eKeyX,
	eKeyY,
	eKeyZ,
	eKeySpace,
	eKeyPlus,
	eKeyMinus,
	eKeyPoint,
	eKeyBack,
	eKeyEnter,
	eKeyShift,
	eKeyCapsLock,
	eKeyMax,
};
#if 0
class CMFCButton;
struct KeyItem
{
	int32_t key;
	CMFCButton* bt;
	int32_t id;
	uint16_t vs;
	uint16_t VS;
};
#endif

using KeyIDMap = std::map<eKeys, int32_t>;
using IDKeyMap = std::map<int32_t, eKeys>;

inline IDKeyMap convert(const KeyIDMap& src)
{
	IDKeyMap dest;
	for (auto& item : src)
	{
		dest.insert({ item.second, item.first });
	}
	return dest;
}


