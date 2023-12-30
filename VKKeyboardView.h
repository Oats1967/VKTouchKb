
// KeyboardView.h: Schnittstelle der CKeyboardView-Klasse
//

#pragma once

#include "VKTouchKbDoc.h"
#include "KeyMap.h"


#define _S32(_a) static_cast<int32_t>(_a)


class CKeyboardView : public CFormView
{
	struct KeyChar
	{
		eKeys c_key;
		uint16_t vs;
		uint16_t VS;
	};
	static const KeyChar c_KeyCharList[_S32(eKeys::eKeyMax)];
	KeyIDMap m_KeyMap;
	IDKeyMap c_IDMap;
	std::array<CMFCButton, int32_t(eKeys::eKeyMax)> m_bt;
	std::array< CRect, int32_t(eKeys::eKeyMax)> m_ButtonRect;
	CFont m_idFont;
	BOOL m_bShift;
	BOOL m_bCapsLock;
	CRect m_SizeRect;

// Attribute
public:
	CVKTouchKbDoc* GetDocument() const;
	CKeyboardView(int32_t id, const KeyIDMap& rMap) noexcept;

// Vorgänge
public:

// Überschreibungen
public:
	virtual void OnDraw(CDC* pDC);  // Überschrieben, um diese Ansicht darzustellen
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

	void SetButtonColor(CMFCButton& bt, COLORREF FaceColor, COLORREF TextColor);
	void SetButtonSize(CMFCButton& bt);
	void SetButtonFont(CMFCButton& bt, CFont* pFont);
	void SendKey(uint16_t c);
	void SendCapsLock();
	void SetButtonText();
	void SetInitialButtonSize();
	void SaveButtonSize();


// Implementierung
public:
	virtual ~CKeyboardView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

public:
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual void OnInitialUpdate();
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);

	CRect GetSizeRect() const
	{ return m_SizeRect;}
	CRect CalcSizeRect() const;
	void SetSize(const CSize& rSize);
};

#ifndef _DEBUG  // Debugversion in KeyboardView.cpp
inline CVKTouchKbDoc* CKeyboardView::GetDocument() const
   { return reinterpret_cast<CVKTouchKbDoc*>(m_pDocument); }
#endif

