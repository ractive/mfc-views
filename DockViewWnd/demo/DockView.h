// DockView.h : main header file for the DOCKVIEW application
//

#if !defined(AFX_DOCKVIEW_H__72901BBE_9E7A_47D7_9DBE_1D7D1A406602__INCLUDED_)
#define AFX_DOCKVIEW_H__72901BBE_9E7A_47D7_9DBE_1D7D1A406602__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CDockViewApp:
// See DockView.cpp for the implementation of this class
//

class CDockViewApp : public CWinApp
{
public:
	CDockViewApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDockViewApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CDockViewApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DOCKVIEW_H__72901BBE_9E7A_47D7_9DBE_1D7D1A406602__INCLUDED_)
