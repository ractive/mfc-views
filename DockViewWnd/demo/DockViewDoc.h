// DockViewDoc.h : interface of the CDockViewDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DOCKVIEWDOC_H__05E92774_82AF_448D_B1A7_2C525D33E020__INCLUDED_)
#define AFX_DOCKVIEWDOC_H__05E92774_82AF_448D_B1A7_2C525D33E020__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CDockViewDoc : public CDocument
{
protected: // create from serialization only
	CDockViewDoc();
	DECLARE_DYNCREATE(CDockViewDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDockViewDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDockViewDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDockViewDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DOCKVIEWDOC_H__05E92774_82AF_448D_B1A7_2C525D33E020__INCLUDED_)
