#if !defined(AFX_MYTREEVIEW_H__217AC6A4_3ECF_45F2_840E_891963079857__INCLUDED_)
#define AFX_MYTREEVIEW_H__217AC6A4_3ECF_45F2_840E_891963079857__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyTreeView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyTreeView view

class CMyTreeView : public CTreeView
{
protected:
	CMyTreeView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CMyTreeView)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyTreeView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CMyTreeView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CMyTreeView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYTREEVIEW_H__217AC6A4_3ECF_45F2_840E_891963079857__INCLUDED_)
