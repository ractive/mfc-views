// TabViewTest.h : main header file for the TABVIEWTEST application
//

#if !defined(AFX_TABVIEWTEST_H__6F5FD726_D250_4592_83A7_89682D92DE13__INCLUDED_)
#define AFX_TABVIEWTEST_H__6F5FD726_D250_4592_83A7_89682D92DE13__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CTabViewTestApp:
// See TabViewTest.cpp for the implementation of this class
//

class CTabViewTestApp : public CWinApp
{
public:
	CTabViewTestApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTabViewTestApp)
	public:
	virtual BOOL InitInstance();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void AddToRecentFileList(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CTabViewTestApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TABVIEWTEST_H__6F5FD726_D250_4592_83A7_89682D92DE13__INCLUDED_)
