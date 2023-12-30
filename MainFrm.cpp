
// MainFrm.cpp: Implementierung der CMainFrame-Klasse
//

#include "pch.h"
#include "VKTouchKb.h"
#include "MainFrm.h"
#include "VKAlphaView.h"
#include "VKNumericView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame


#define _C(_a) static_cast<char>(_a)


#define C_SOH		_C(0x01)
#define C_STX		_C(0x02)
#define C_ETX		_C(0x03)
#define C_CR		_C(0x0D)
#define C_GP		_C(0x03)
#define C_P			_C(0x50)
#define C_ETB		_C(0x17)
#define C_ENQ		_C(0x05)
#define C_EOT		_C(0x04)
#define C_NAK		_C(0x15)


IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
#if 0
	ON_COMMAND_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnApplicationLook)
	ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnUpdateApplicationLook)
#endif
	ON_WM_CREATE()
END_MESSAGE_MAP()

// CMainFrame-Erstellung/Zerstörung

CMainFrame::CMainFrame() noexcept :
	m_port{ 2000 }
	, m_pAlphaView{ nullptr }
	, m_pNumericView{ nullptr }
	, m_AlphaSize{ 100, 100 }
	, m_NumericSize{ 100, 100 }
	, m_nLayout{ eLayout::TKL_ALPHA }
{
	// TODO: Hier Code für die Memberinitialisierung einfügen
}

CMainFrame::~CMainFrame()
{
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.dwExStyle = WS_EX_TOPMOST | WS_EX_NOACTIVATE;  // or others you want
	cs.hMenu = NULL; // Add this one line code
	cs.style = WS_OVERLAPPED | WS_BORDER;// WS_OVERLAPPED;
	//cs.style &= ~(FWS_ADDTOTITLE | FWS_PREFIXTITLE);
	cs.lpszName = _T("");
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Ändern Sie hier die Fensterklasse oder die Darstellung, indem Sie
	//  CREATESTRUCT cs modifizieren.
	return TRUE;
}

// CMainFrame-Diagnose

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Fügen Sie Ihren spezialisierten Erstellcode hier ein.

	m_nLayout = eLayout::TKL_ALPHA;
#if 0
	SetWindowPos(m_nLayout);
	SetSize(m_nLayout);
#endif
	return 0;
}


BOOL CMainFrame::LoadFrame(UINT nIDResource, DWORD dwDefaultStyle, CWnd* pParentWnd, CCreateContext* pContext)
{
	BOOL bRet = CFrameWnd::LoadFrame(nIDResource, dwDefaultStyle, pParentWnd, pContext);
	if (bRet)
	{
		ModifyStyle(WS_CAPTION, 0, SWP_FRAMECHANGED);
	}
	m_sListener.SetParentDlg(this);
	m_sConnected.SetParentDlg(this);
	m_sListener.Create(m_port);
	if (m_sListener.Listen() == FALSE)
	{
		AfxMessageBox(_T("Unable to Listen on that port, please try another port"));
	}
	return bRet;
}
//***********************************************************************************************************************************
//***********************************************************************************************************************************
void CMainFrame::SetWindowPos(eLayout l)
{
	if (l == eLayout::TKL_ALPHA)
	{
		int32_t x = 0;
		int32_t y = 0;
		x = 10;
		y = 600;
		::SetWindowPos(m_hWnd, HWND_TOPMOST, x, y, -1, -1, SWP_NOZORDER | SWP_NOSIZE);
	}
}
//***********************************************************************************************************************************
//***********************************************************************************************************************************
CSize CMainFrame::GetSizeView(eLayout l) const
{
	CSize aSize;
	if (l == eLayout::TKL_ALPHA)
	{
		aSize = m_AlphaSize;
	}
	else if (l == eLayout::TKL_NUMBER)
	{
		aSize = m_NumericSize;
	}
	else
	{
		ASSERT(FALSE);
	}
	return aSize;
}
//***********************************************************************************************************************************
//***********************************************************************************************************************************
CKeyboardView* CMainFrame::GetKeyboardView(eLayout l) const
{
	CKeyboardView* pView = nullptr;
	if (l == eLayout::TKL_ALPHA)
	{
		pView = (CKeyboardView*)m_pAlphaView;
		ASSERT(pView);
	}
	else if (l == eLayout::TKL_NUMBER)
	{
		pView = (CKeyboardView*)m_pNumericView;
		ASSERT(pView);
	}
	else
	{
		ASSERT(FALSE);
	}
	return pView;
}
//***********************************************************************************************************************************
//***********************************************************************************************************************************
void CMainFrame::SetSize(eLayout l)
{
	auto* pView = GetKeyboardView(l);
	if ( pView )
	{
		auto rRect = pView->GetSizeRect();
		auto rSize = GetSizeView(l);
		CSize NewSize = CSize(rRect.Width() * rSize.cx / 100 + 6, rRect.Height() * rSize.cy / 100 + 6);
		::SetWindowPos(m_hWnd, HWND_TOPMOST, -1, -1, NewSize.cx, NewSize.cy, SWP_NOZORDER | SWP_NOMOVE);
		pView->SetSize(rSize);
	}
}
//***********************************************************************************************************************************
//***********************************************************************************************************************************
void CMainFrame::SetLayout(eLayout l)
{
	if (l != m_nLayout)
	{
		m_nLayout = l;
		auto oldView = GetActiveView();
		auto newview = CreateView(m_nLayout);
		if (newview != oldView)
		{
			AddViewToDocument(oldView, newview);
			SetActiveView(newview);
			RecalcLayout();
		}
		SetSize(l);
		SetWindowPos(l);
	}
}
//******************************************************************************************************
//******************************************************************************************************
void CMainFrame::OnHide(char* str, int32_t len)
{
	ASSERT(str[0] == C_STX);
	ASSERT(str[1] == 0x2);
	ASSERT(str[2] == _C(TKCommand::eTKSetHide));

	ShowWindow(SW_HIDE);
}
//******************************************************************************************************
//******************************************************************************************************
void CMainFrame::OnSetShowPoint(char* str, int32_t len)
{
	ASSERT(str[0] == C_STX);
	ASSERT(str[1] == 0x7);
	ASSERT(str[2] == _C(TKCommand::eTKSetShowPoint));
	auto nLayout = eLayout(str[3]);
	SetLayout(nLayout);
	ASSERT(nLayout == eLayout::TKL_ALPHA || nLayout == eLayout::TKL_NUMBER);
	uint16_t x = MAKEWORD(str[4], str[5]);
	uint16_t y = MAKEWORD(str[6], str[7]);

	::SetWindowPos(m_hWnd, HWND_TOPMOST, x, y, -1, -1, SWP_NOZORDER | SWP_NOSIZE);
	ShowWindow(SW_SHOW);
}
//******************************************************************************************************
//******************************************************************************************************
void CMainFrame::OnSetShow(char* str, int32_t len)
{
	ASSERT(str[0] == C_STX);
	ASSERT(str[1] == 0x3);
	ASSERT(str[2] == _C(TKCommand::eTKSetShow));
	auto nLayout = eLayout(str[3]);
	ASSERT(nLayout == eLayout::TKL_ALPHA || nLayout == eLayout::TKL_NUMBER);
	SetLayout(nLayout);
	ShowWindow(SW_SHOW);
}
//******************************************************************************************************
//******************************************************************************************************
void CMainFrame::OnSetSize(char* str, int32_t len)
{
	ASSERT(str[0] == C_STX);
	ASSERT(str[1] == 0x7);
	ASSERT(str[2] == _C(TKCommand::eTKSetSize));
	auto nLayout = eLayout(str[3]);
	ASSERT(nLayout == eLayout::TKL_ALPHA || nLayout == eLayout::TKL_NUMBER);
	uint16_t w = MAKEWORD(str[4], str[5]);
	uint16_t h = MAKEWORD(str[6], str[7]);

	BOOL bChanged = FALSE;
	if (nLayout == eLayout::TKL_ALPHA)
	{
		bChanged = (nLayout == m_nLayout) && (m_AlphaSize.cx != w) || (m_AlphaSize.cy != h);
		m_AlphaSize.cx = w;
		m_AlphaSize.cy = h;
	}
	else if (nLayout == eLayout::TKL_NUMBER)
	{
		bChanged = (nLayout == m_nLayout) && (m_NumericSize.cx != w) || (m_NumericSize.cy != h);
		m_NumericSize.cx = w;
		m_NumericSize.cy = h;
	}
	else
	{
		ASSERT(FALSE);
	}
	if (bChanged)
	{
		ShowWindow(SW_HIDE);
		SetSize(nLayout);
		ShowWindow(SW_SHOW);
	}
}
//******************************************************************************************************
//******************************************************************************************************
void CMainFrame::ProcessMessage(char* str, int32_t len)
{
	if (len > 0)
	{
		if (str[0] == C_STX)
		{
			switch (TKCommand(str[2]))
			{
			case TKCommand::eTKSetSize:
				OnSetSize(str, len);
				break;

			case TKCommand::eTKSetShowPoint:
				OnSetShowPoint(str, len);
				break;

			case TKCommand::eTKSetShow:
				OnSetShow(str, len);
				break;

			case TKCommand::eTKSetHide:
				OnHide(str, len);
				break;
			}
		}
	}
}
//******************************************************************************************************
//******************************************************************************************************
void CMainFrame::OnReceive()
{
	char pBuf[1025];
	auto iLen = m_sConnected.Receive(pBuf, sizeof(pBuf));
	if (iLen == SOCKET_ERROR)
	{
		AfxMessageBox(_T("Could not Receive"));
	}
	else
	{
		ProcessMessage(pBuf, iLen);
	}
}
//******************************************************************************************************
//******************************************************************************************************
void CMainFrame::OnClose()
{
	//AfxMessageBox(_T("Socket Is Closed!!!"));
	m_sConnected.Close();
	m_sListener.Close();
}
//******************************************************************************************************
//******************************************************************************************************
void CMainFrame::OnAccept()
{
	CString strIP;
	UINT port;
	if (m_sListener.Accept(m_sConnected))
	{
		m_sConnected.GetSockName(strIP, port);
		//m_status = "Client Connected,IP :" + strIP;
		m_sConnected.Send("Connected To Server", strlen("Connected To  Server"));
	}
	else
	{
		AfxMessageBox(_T("Cannot Accept Connection"));
	}
}

//***************************************************************************************************
//***************************************************************************************************
void CMainFrame::AddViewToDocument(CView* pOldView, CView* pNewView)
{
	if (pOldView != pNewView)
	{
		CDocument* pDoc = NULL;

		if (pOldView != NULL)
		{
			pDoc = pOldView->GetDocument();
		}
		else if (pNewView != NULL)
		{
			pDoc = pNewView->GetDocument();
		}
		if (pDoc)
		{
			// Show the newly active view and hide the inactive view.
			if (pOldView)
			{
				BOOL bAutoDelete = pDoc->m_bAutoDelete;
				pOldView->ShowWindow(SW_HIDE);
				pDoc->m_bAutoDelete = FALSE;
				// Dettach existing view
				pDoc->RemoveView(pOldView);
				pDoc->m_bAutoDelete = bAutoDelete;
			}
			if (pNewView)
			{
				// Attach new view
				pDoc->AddView(pNewView);

				pNewView->ShowWindow(SW_SHOW);
			}
		}
	}
}
//***************************************************************************************************
//***************************************************************************************************
CView* CMainFrame::CreateView(eLayout l)
{
	CView* pNewView = NULL;

	if (l == eLayout::TKL_ALPHA)
	{
		if (! m_pAlphaView)
		{
			if (! m_pNumericView)
			{
				m_pNumericView = GetActiveView();
			}
			// create the new view
			m_pAlphaView = new CVKAlphaView;
			m_pAlphaView->Create(NULL, NULL, AFX_WS_DEFAULT_VIEW, CRect(0, 0, 0, 0), this, AFX_IDW_PANE_FIRST, NULL);
			m_pAlphaView->OnInitialUpdate();
			m_AlphaRect = ((CKeyboardView*)m_pAlphaView)->GetSizeRect();
		}
		pNewView = m_pAlphaView;
	}
	else if (l == eLayout::TKL_NUMBER)
	{
		if (!m_pNumericView)
		{
			if (!m_pAlphaView)
			{
				m_pAlphaView = GetActiveView();
			}
			// create the new view
			m_pNumericView = new CVKNumericView;
			m_pNumericView->Create(NULL, NULL, AFX_WS_DEFAULT_VIEW, CRect(0, 0, 0, 0), this, AFX_IDW_PANE_FIRST, NULL);
			m_pNumericView->OnInitialUpdate();
			m_NumericRect = ((CKeyboardView*)m_pNumericView)->GetSizeRect();
		}
		pNewView = m_pNumericView;
	}
	return pNewView;
}



void CMainFrame::ActivateFrame(int nCmdShow)
{
	m_pAlphaView = GetActiveView();
	ASSERT(m_pAlphaView);
	m_AlphaRect = ((CKeyboardView*)m_pAlphaView)->GetSizeRect();
	SetSize(m_nLayout);
	SetWindowPos(m_nLayout);
	CFrameWnd::ActivateFrame(nCmdShow);
}
