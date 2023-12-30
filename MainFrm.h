
// MainFrm.h: Schnittstelle der CMainFrame-Klasse
//

#pragma once
#include "MyEchoSocket.h"


class CKeyboardView;

class CMainFrame : public CFrameWnd
{
	enum class TKCommand : uint8_t
	{
		eTKSetSize = 0x11,
		eTKSetShowPoint = 0x13,
		eTKSetShow = 0x14,
		eTKSetHide = 0x15,
	};

	enum class eLayout : uint16_t
	{
		TKL_NONE = 0,
		TKL_ALPHA,
		TKL_NUMBER,
		TKL_MAX
	};

protected: // Nur aus Serialisierung erstellen
	CMainFrame() noexcept;
	DECLARE_DYNCREATE(CMainFrame)

// Attribute
public:
	MyEchoSocket m_sListener;
	MyEchoSocket m_sConnected;
	int32_t m_port;
	eLayout m_nLayout;

	CView* m_pAlphaView;
	CView* m_pNumericView;

	CSize m_AlphaSize;
	CSize m_NumericSize;

	CRect m_AlphaRect;
	CRect m_NumericRect;

// Vorgänge
public:
	void SetLayout(eLayout);
	void SetSize(eLayout);
	void SetWindowPos(eLayout l);
	void ProcessMessage(char* str, int32_t len);
	void OnHide(char* str, int32_t len);
	void OnSetShowPoint(char* str, int32_t len);
	void OnSetShow(char* str, int32_t len);
	void OnSetSize(char* str, int32_t len);

	void AddViewToDocument(CView* pOldView, CView* pNewView);
	CView* CreateView(eLayout l);
	CKeyboardView* GetKeyboardView(eLayout l) const;
	CSize GetSizeView(eLayout l) const;

	void OnAccept();
	void OnReceive();
	void OnClose();

// Überschreibungen
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementierung
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif


// Generierte Funktionen für die Meldungstabellen
protected:
	afx_msg void OnApplicationLook(UINT id);
	afx_msg void OnUpdateApplicationLook(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()

public:
//	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle = WS_OVERLAPPEDWINDOW, const RECT& rect = rectDefault, CWnd* pParentWnd = NULL, LPCTSTR lpszMenuName = NULL, DWORD dwExStyle = 0, CCreateContext* pContext = NULL);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL LoadFrame(UINT nIDResource, DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, CWnd* pParentWnd = NULL, CCreateContext* pContext = NULL);
	virtual void ActivateFrame(int nCmdShow = -1);
};


