#if !defined(AFX_TESTHTMLVIEW_H__1D5095CA_71B5_4411_B401_82F116D2B2F4__INCLUDED_)
#define AFX_TESTHTMLVIEW_H__1D5095CA_71B5_4411_B401_82F116D2B2F4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TestHtmlView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTestHtmlView html view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif
#include <afxhtml.h>

class CTestHtmlView : public CHtmlView
{
protected:
	CTestHtmlView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CTestHtmlView)

// html Data
public:
	//{{AFX_DATA(CTestHtmlView)
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestHtmlView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CTestHtmlView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CTestHtmlView)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTHTMLVIEW_H__1D5095CA_71B5_4411_B401_82F116D2B2F4__INCLUDED_)
