
// VKNumericView.h: Schnittstelle der CVKNumericView-Klasse
//

#pragma once

#include "VKKeyboardView.h"


class CVKNumericView : public CKeyboardView
{
protected: // Nur aus Serialisierung erstellen
	DECLARE_DYNCREATE(CVKNumericView)

	enum { IDD = IDD_NUMERIC };

// Attribute
public:
	CVKNumericView() noexcept;
};
