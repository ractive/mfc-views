#if !defined(AFX_TESTTABVIEW_H__E4588F78_3AF1_497D_852D_10CC442B19F1__INCLUDED_)
#define AFX_TESTTABVIEW_H__E4588F78_3AF1_497D_852D_10CC442B19F1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TestTabView.h : header file
//

#include "TabView.h"

/////////////////////////////////////////////////////////////////////////////
// CTestTabView view

class CTestTabView : public CTabView
{
protected:
	CTestTabView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CTestTabView)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestTabView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CTestTabView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CTestTabView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTTABVIEW_H__E4588F78_3AF1_497D_852D_10CC442B19F1__INCLUDED_)
