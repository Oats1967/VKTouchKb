
// VKTouchKb.h: Hauptheaderdatei für die VKTouchKb-Anwendung
//
#pragma once

#ifndef __AFXWIN_H__
	#error "'pch.h' vor dieser Datei für PCH einschließen"
#endif

#include "resource.h"       // Hauptsymbole


// CVKTouchKbApp:
// Siehe VKTouchKb.cpp für die Implementierung dieser Klasse
//

class CVKTouchKbApp : public CWinApp
{
public:
	CVKTouchKbApp() noexcept;


// Überschreibungen
public:
	virtual BOOL InitInstance();

// Implementierung
	UINT  m_nAppLook;
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CVKTouchKbApp theApp;
