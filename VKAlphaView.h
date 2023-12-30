
// VKAlphaView.h: Schnittstelle der CVKAlphaView-Klasse
//

#pragma once

#include "VKKeyboardView.h"



class CVKAlphaView : public CKeyboardView
{
protected: // Nur aus Serialisierung erstellen
	DECLARE_DYNCREATE(CVKAlphaView)

	enum { IDD = IDD_ALPHA };

// Attribute
public:
	CVKAlphaView() noexcept;

};

