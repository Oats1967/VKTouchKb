
// VKAlphaView.cpp: Implementierung der CVKAlphaView-Klasse
//

#include "pch.h"
#include "VKTouchKb.h"
#include "VKTouchKbDoc.h"
#include "VKAlphaView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CVKAlphaView

IMPLEMENT_DYNCREATE(CVKAlphaView, CKeyboardView)


// CVKAlphaView-Erstellung/Zerstörung

CVKAlphaView::CVKAlphaView() noexcept
	: CKeyboardView(CVKAlphaView::IDD,
		 {
							{ eKeys::eKey0, IDC_ALPHA_0 },
							{ eKeys::eKey1,  IDC_ALPHA_1},
							{ eKeys::eKey2,  IDC_ALPHA_2},
							{ eKeys::eKey3,  IDC_ALPHA_3},
							{ eKeys::eKey4,  IDC_ALPHA_4},
							{ eKeys::eKey5,  IDC_ALPHA_5},
							{ eKeys::eKey6,  IDC_ALPHA_6},
							{ eKeys::eKey7,  IDC_ALPHA_7},
							{ eKeys::eKey8,  IDC_ALPHA_8},
							{ eKeys::eKey9,  IDC_ALPHA_9},
							{ eKeys::eKeyQ, IDC_ALPHA_Q},
							{ eKeys::eKeyW, IDC_ALPHA_W},
							{ eKeys::eKeyE, IDC_ALPHA_E},
							{ eKeys::eKeyR, IDC_ALPHA_R},
							{ eKeys::eKeyT, IDC_ALPHA_T},
							{ eKeys::eKeyZ, IDC_ALPHA_Z},
							{ eKeys::eKeyU, IDC_ALPHA_U},
							{ eKeys::eKeyI, IDC_ALPHA_I},
							{ eKeys::eKeyO, IDC_ALPHA_O},
							{ eKeys::eKeyP, IDC_ALPHA_P},
							{ eKeys::eKeyA, IDC_ALPHA_A},
							{ eKeys::eKeyS, IDC_ALPHA_S},
							{ eKeys::eKeyD, IDC_ALPHA_D},
							{ eKeys::eKeyF, IDC_ALPHA_F},
							{ eKeys::eKeyG, IDC_ALPHA_G},
							{ eKeys::eKeyH, IDC_ALPHA_H},
							{ eKeys::eKeyJ, IDC_ALPHA_J},
							{ eKeys::eKeyK, IDC_ALPHA_K},
							{ eKeys::eKeyL, IDC_ALPHA_L},
							{ eKeys::eKeyY, IDC_ALPHA_Y},
							{ eKeys::eKeyX, IDC_ALPHA_X},
							{ eKeys::eKeyC, IDC_ALPHA_C},
							{ eKeys::eKeyV, IDC_ALPHA_V},
							{ eKeys::eKeyB, IDC_ALPHA_B},
							{ eKeys::eKeyN, IDC_ALPHA_N},
							{ eKeys::eKeyM, IDC_ALPHA_M},
							{ eKeys::eKeySpace, IDC_ALPHA_SPACE},
							{ eKeys::eKeyPlus, IDC_ALPHA_PLUS},
							{ eKeys::eKeyMinus, IDC_ALPHA_MINUS},
							{ eKeys::eKeyPoint, IDC_ALPHA_POINT},
							{ eKeys::eKeyBack, IDC_ALPHA_BACK},
							{ eKeys::eKeyEnter, IDC_ALPHA_ENTER},
							{ eKeys::eKeyCapsLock, IDC_ALPHA_CAPS},
							{ eKeys::eKeyShift, IDC_ALPHA_SHIFT}
		})
{
}

