
// VKNumericView.cpp: Implementierung der CVKNumericView-Klasse
//

#include "pch.h"
#include "VKTouchKb.h"
#include "VKNumericView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CVKNumericView

IMPLEMENT_DYNCREATE(CVKNumericView, CKeyboardView)

// CVKNumericView-Erstellung/Zerstörung

CVKNumericView::CVKNumericView() noexcept
	: CKeyboardView(CVKNumericView::IDD,
		 {
						{ eKeys::eKey0, IDC_NUMERIC_0 },
						{ eKeys::eKey1,  IDC_NUMERIC_1},
						{ eKeys::eKey2,  IDC_NUMERIC_2},
						{ eKeys::eKey3,  IDC_NUMERIC_3},
						{ eKeys::eKey4,  IDC_NUMERIC_4},
						{ eKeys::eKey5,  IDC_NUMERIC_5},
						{ eKeys::eKey6,  IDC_NUMERIC_6},
						{ eKeys::eKey7,  IDC_NUMERIC_7},
						{ eKeys::eKey8,  IDC_NUMERIC_8},
						{ eKeys::eKey9,  IDC_NUMERIC_9},
						{ eKeys::eKeyPlus, IDC_NUMERIC_PLUS},
						{ eKeys::eKeyMinus, IDC_NUMERIC_MINUS},
						{ eKeys::eKeyPoint, IDC_NUMERIC_POINT},
						{ eKeys::eKeyBack, IDC_NUMERIC_BACK},
						{ eKeys::eKeyEnter, IDC_NUMERIC_ENTER}
		})
{
}


