
// KeyboardView.cpp: Implementierung der CKeyboardView-Klasse
//

#include "pch.h"
#include "framework.h"
#include "VKTouchKb.h"
#include "VKTouchKbDoc.h"
#include "VKKeyboardView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


static COLORREF TextColor   = RGB(255, 255, 255);
static COLORREF FaceColor   = RGB(140, 140, 140);
static COLORREF ReturnColor = RGB(0, 140, 0);
static COLORREF ShiftColor  = RGB(140, 0, 0);



const CKeyboardView::KeyChar CKeyboardView::c_KeyCharList[_S32(eKeys::eKeyMax)] = {
	{ eKeys::eKey0,  '0', '0' },
	{ eKeys::eKey1,  '1', '1' },
	{ eKeys::eKey2,  '2', '2' },
	{ eKeys::eKey3,  '3', '3' },
	{ eKeys::eKey4,  '4', '4' },
	{ eKeys::eKey5,  '5', '5' },
	{ eKeys::eKey6,  '6', '6' },
	{ eKeys::eKey7,  '7', '7' },
	{ eKeys::eKey8,  '8', '8' },
	{ eKeys::eKey9,  '9', '9' },
	{ eKeys::eKeyA,  'a', 'A' },
	{ eKeys::eKeyB,  'b', 'B' },
	{ eKeys::eKeyC,  'c', 'C' },
	{ eKeys::eKeyD,  'd', 'D' },
	{ eKeys::eKeyE,  'e', 'E' },
	{ eKeys::eKeyF,  'f', 'F' },
	{ eKeys::eKeyG,  'g', 'G' },
	{ eKeys::eKeyH,  'h', 'H' },
	{ eKeys::eKeyI,  'i', 'I' },
	{ eKeys::eKeyJ,  'j', 'J' },
	{ eKeys::eKeyK,  'k', 'K' },
	{ eKeys::eKeyL,  'l', 'L' },
	{ eKeys::eKeyM,  'm', 'M' },
	{ eKeys::eKeyN,  'n', 'N' },
	{ eKeys::eKeyO,  'o', 'O' },
	{ eKeys::eKeyP,  'p', 'P' },
	{ eKeys::eKeyQ,  'q', 'Q' },
	{ eKeys::eKeyR,  'r', 'R' },
	{ eKeys::eKeyS,  's', 'S' },
	{ eKeys::eKeyT,  't', 'T' },
	{ eKeys::eKeyU,  'u', 'U' },
	{ eKeys::eKeyV,  'v', 'V' },
	{ eKeys::eKeyW,  'w', 'W' },
	{ eKeys::eKeyX,  'x', 'X' },
	{ eKeys::eKeyY,  'y', 'Y' },
	{ eKeys::eKeyZ,  'z', 'Z' },
	{ eKeys::eKeySpace,		VK_SPACE, VK_SPACE },
	{ eKeys::eKeyPlus,		VK_OEM_PLUS, VK_OEM_PLUS },
	{ eKeys::eKeyMinus,		VK_OEM_MINUS, VK_OEM_MINUS },
	{ eKeys::eKeyPoint,		VK_OEM_PERIOD, VK_OEM_PERIOD },
	{ eKeys::eKeyBack,		VK_BACK, VK_BACK },
	{ eKeys::eKeyEnter,		VK_RETURN, VK_RETURN},
	{ eKeys::eKeyShift,		VK_SHIFT, VK_SHIFT },
	{ eKeys::eKeyCapsLock,	VK_CAPITAL, VK_CAPITAL}
};


// CKeyboardView
CKeyboardView::CKeyboardView(int32_t id, const KeyIDMap& rMap) noexcept
	: CFormView(id)
	, m_KeyMap { rMap }
	, c_IDMap  { convert(rMap) }
	, m_bShift{ FALSE }
	, m_bCapsLock{ FALSE }

{
	ASSERT(m_KeyMap.size() == c_IDMap.size());
	m_idFont.CreateFont(20, 0, 0, 0, FW_BOLD,
		FALSE, FALSE, 0, ANSI_CHARSET,
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("Courier"));

#if _DEBUG
	for (int32_t i = 0; i < _S32(eKeys::eKeyMax); i++)
	{
		ASSERT(_S32(c_KeyCharList[i].c_key) == i);
	}
#endif
}

CKeyboardView::~CKeyboardView()
{
}

BOOL CKeyboardView::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.dwExStyle |= WS_EX_NOACTIVATE;  // or others you want
	return CView::PreCreateWindow(cs);
}

// CKeyboardView-Zeichnung

void CKeyboardView::OnDraw(CDC* /*pDC*/)
{
	CVKTouchKbDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: Code zum Zeichnen der nativen Daten hinzufügen
}


// CKeyboardView-Diagnose

#ifdef _DEBUG
void CKeyboardView::AssertValid() const
{
	CView::AssertValid();
}

void CKeyboardView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CVKTouchKbDoc* CKeyboardView::GetDocument() const // Nichtdebugversion ist inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CVKTouchKbDoc)));
	return (CVKTouchKbDoc*)m_pDocument;
}
#endif //_DEBUG


void CKeyboardView::SendKey(uint16_t c)
{
	INPUT input;
	ZeroMemory(&input, sizeof(input));

	if (m_bShift)
	{
		input.type = INPUT_KEYBOARD;
		input.ki.wVk = VK_LSHIFT;
		input.ki.dwFlags = KEYEVENTF_EXTENDEDKEY; // 0
		SendInput(1, &input, sizeof(INPUT));
	}
	input.type = INPUT_KEYBOARD;
	input.ki.wVk = c;
	input.ki.dwFlags = KEYEVENTF_EXTENDEDKEY; // 0
	SendInput(1, &input, sizeof(INPUT));

	input.type = INPUT_KEYBOARD;
	input.ki.wVk = c;
	input.ki.dwFlags = KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP; // 0
	SendInput(1, &input, sizeof(INPUT));

	if (m_bShift)
	{
		input.type = INPUT_KEYBOARD;
		input.ki.wVk = VK_LSHIFT;
		input.ki.dwFlags = KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP; // 0
		SendInput(1, &input, sizeof(INPUT));
	}
}

void CKeyboardView::SendCapsLock()
{
	INPUT input[2] = {};
	ZeroMemory(&input, sizeof(input));

	input[0].type = INPUT_KEYBOARD;
	input[0].ki.wVk = VK_CAPITAL;
	input[0].ki.dwFlags = KEYEVENTF_EXTENDEDKEY; // 0
	input[1].type = INPUT_KEYBOARD;
	input[1].ki.wVk = VK_CAPITAL;
	input[1].ki.dwFlags = KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP; // 0
	UINT uSent = SendInput(2, input, sizeof(INPUT));
}


void CKeyboardView::DoDataExchange(CDataExchange* pDX)
{
	for (auto& item : m_KeyMap)
	{
		DDX_Control(pDX, item.second, m_bt[_S32(item.first)]);
	}
	CFormView::DoDataExchange(pDX);
}

void CKeyboardView::SetButtonSize(CMFCButton& bt)
{
	CRect rect;
	bt.GetWindowRect(rect);
	bt.SetWindowPos(nullptr, -1, -1, _S32(rect.Width() * 0.9), _S32(rect.Height() * 0.9), SWP_NOMOVE | SWP_NOZORDER);
}


void CKeyboardView::SetButtonColor(CMFCButton& bt, COLORREF FaceColor, COLORREF TextColor)
{
	bt.EnableWindowsTheming(FALSE);		// (important!)
	bt.SetFaceColor(FaceColor);		// Change to your desired Background Color
	bt.SetTextColor(TextColor);	// Change it to your desired Foreground Color}
}

void CKeyboardView::SetButtonFont(CMFCButton& bt, CFont* pFont)
{
	if (pFont)
	{
		bt.SetFont(pFont);
	}
}

void CKeyboardView::SetButtonText()
{
	for (auto& item : m_KeyMap)
	{
		auto id = _S32(item.first);
		if ((id >= _S32(eKeys::eKeyA)) &&
			(id <= _S32(eKeys::eKeyZ)))
		{
			CString s(char(c_KeyCharList[id].vs));
			CString S(char(c_KeyCharList[id].VS));
			m_bt[id].SetWindowText((m_bShift|| m_bCapsLock) ? S : s);
		}
	}
}

CRect CKeyboardView::CalcSizeRect() const
{
	CRect aRect;

	if (!m_KeyMap.empty())
	{
		auto id = _S32(m_KeyMap.begin()->first);
		m_bt[id].GetWindowRect(aRect);
		ScreenToClient(aRect);

		for (auto& item : m_KeyMap)
		{
			auto id = _S32(item.first);
			CRect rc;
			m_bt[id].GetWindowRect(rc);
			ScreenToClient(rc);
			aRect.UnionRect(aRect, rc);
		}
	}
	return aRect;
}


void CKeyboardView::SetSize(const CSize& rSize)
{
	CRect rViewRect;
	GetWindowRect(rViewRect);

	for (auto& item : m_KeyMap)
	{
		auto id = _S32(item.first);
		CRect rect = m_ButtonRect[id];
		rect.left = rect.left * rSize.cx / 100;
		rect.right = rect.right * rSize.cx / 100;
		rect.top = rect.top * rSize.cy / 100;
		rect.bottom = rect.bottom * rSize.cy / 100;

		//rect += rViewRect.TopLeft();
		m_bt[id].SetWindowPos(nullptr, rect.left, rect.top, rect.Width(), rect.Height(), SWP_NOZORDER);
	}
}


void CKeyboardView::SetInitialButtonSize()
{
	for (auto& item : m_KeyMap)
	{
		SetButtonSize(m_bt[_S32(item.first)]);
	}
}

void CKeyboardView::SaveButtonSize()
{
	CRect rViewRect;
	GetWindowRect(rViewRect);

	for (auto& item : m_KeyMap)
	{
		int32_t id = _S32(item.first);
		m_bt[id].GetWindowRect(m_ButtonRect[id]);

		m_ButtonRect[id] -= rViewRect.TopLeft();
		int k = 0;
	}
}

void CKeyboardView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	m_bShift = FALSE;
	m_bCapsLock = FALSE;

	UpdateData(TRUE);
	SetInitialButtonSize();
	SaveButtonSize();
	m_SizeRect = CalcSizeRect();

	for (auto& item : m_KeyMap)
	{
		if ((item.first == eKeys::eKeyEnter))
		{
			SetButtonColor(m_bt[_S32(item.first)], ReturnColor, TextColor);
		}
		else
		{
			SetButtonColor(m_bt[_S32(item.first)], FaceColor, TextColor);
			if ((item.first != eKeys::eKeyShift) && (item.first != eKeys::eKeyCapsLock))
			{
				SetButtonFont(m_bt[_S32(item.first)], &m_idFont);
			}
		}
	}
	SetButtonText();
	SetScrollSizes(MM_TEXT, CSize(0, 0));
}


BOOL CKeyboardView::OnCommand(WPARAM wParam, LPARAM lParam)
{
	auto id = _S32(wParam);
	auto it = c_IDMap.find(id);
	if (it != c_IDMap.cend())
	{
		if ((it->second == eKeys::eKeyShift))
		{
			m_bShift = !m_bShift;
			SetButtonColor(m_bt[_S32(eKeys::eKeyShift)], (m_bShift)?ShiftColor: FaceColor, TextColor);
			SetButtonText();
		}
		else if ((it->second == eKeys::eKeyCapsLock))
		{
			m_bCapsLock = ! m_bCapsLock;
			SendCapsLock();
			SetButtonText();
			SetButtonColor(m_bt[_S32(eKeys::eKeyCapsLock)], (m_bCapsLock) ? ShiftColor : FaceColor, TextColor);
		}
		else
		{
			SendKey(c_KeyCharList[_S32(it->second)].VS);
			if (m_bShift)
			{
				m_bShift = FALSE;
				SetButtonColor(m_bt[_S32(eKeys::eKeyShift)], FaceColor, TextColor);
				SetButtonText();
			}
		}
	}
	return CFormView::OnCommand(wParam, lParam);
}