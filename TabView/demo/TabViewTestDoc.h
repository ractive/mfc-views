// TabViewTestDoc.h : interface of the CTabViewTestDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TABVIEWTESTDOC_H__28D7A0B9_0393_43C4_9D21_2B5E30E707E3__INCLUDED_)
#define AFX_TABVIEWTESTDOC_H__28D7A0B9_0393_43C4_9D21_2B5E30E707E3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CTabViewTestDoc : public CDocument
{
protected: // create from serialization only
	CTabViewTestDoc();
	DECLARE_DYNCREATE(CTabViewTestDoc)

// Attributes
public:
	CString m_sUrl;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTabViewTestDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTabViewTestDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTabViewTestDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TABVIEWTESTDOC_H__28D7A0B9_0393_43C4_9D21_2B5E30E707E3__INCLUDED_)
