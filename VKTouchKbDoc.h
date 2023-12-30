
// VKTouchKbDoc.h: Schnittstelle der CVKTouchKbDoc-Klasse
//


#pragma once




class CVKTouchKbDoc : public CDocument
{
protected: // Nur aus Serialisierung erstellen
	CVKTouchKbDoc() noexcept;
	DECLARE_DYNCREATE(CVKTouchKbDoc)

// Attribute
public:

// Vorgänge
public:

// Überschreibungen
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementierung
public:
	virtual ~CVKTouchKbDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generierte Funktionen für die Meldungstabellen
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Hilfsfunktion, die Suchinhalt für Suchhandler festlegt
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
