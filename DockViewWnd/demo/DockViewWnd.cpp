// DockViewWnd.cpp : implementation file
//

#include "stdafx.h"
#include "DockView.h"
#include "DockViewWnd.h"
#include <afxpriv.h>
#include "ViewBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDockViewWnd

#ifndef _UNICODE
#define _UNICODE_SUFFIX
#else
#define _UNICODE_SUFFIX _T("u")
#endif

#ifndef _DEBUG
#define _DEBUG_SUFFIX
#else
#define _DEBUG_SUFFIX _T("d")
#endif

#ifdef _AFXDLL
#define _STATIC_SUFFIX
#else
#define _STATIC_SUFFIX _T("s")
#endif

#define AFX_WNDCLASS(s) \
	_T("Afx") _T(s) _T("42") _STATIC_SUFFIX _UNICODE_SUFFIX _DEBUG_SUFFIX

#define AFX_WND             AFX_WNDCLASS("Wnd")
#define AFX_WNDCONTROLBAR   AFX_WNDCLASS("ControlBar")
#define AFX_WNDMDIFRAME     AFX_WNDCLASS("MDIFrame")
#define AFX_WNDFRAMEORVIEW  AFX_WNDCLASS("FrameOrView")
#define AFX_WNDOLECONTROL   AFX_WNDCLASS("OleControl")

#define AFX_WNDMDIFRAME_REG             0x00004


CDockViewWnd::CDockViewWnd()
{
	m_uLastID = AFX_IDW_PANE_FIRST + 64;
}

CDockViewWnd::~CDockViewWnd()
{
	POSITION pos = GetFirstBar();
	while (pos) {
		CViewBar * pBar = GetNextBar(pos);
		pBar->DestroyWindow();
		delete pBar;
	}

	m_aBars.RemoveAll();
}


BEGIN_MESSAGE_MAP(CDockViewWnd, CWnd)
	//{{AFX_MSG_MAP(CDockViewWnd)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDockViewWnd message handlers

BOOL CDockViewWnd::Create(CWnd* pParentWnd, CCreateContext* pContext, UINT nID) 
{
	ASSERT(pParentWnd != NULL);
	ASSERT(nID != 0);

	DWORD dwStyle = WS_CHILD | WS_VISIBLE;

	// the Windows scroll bar styles bits turn on the smart scrollbars
	DWORD dwCreateStyle = dwStyle & ~(WS_HSCROLL|WS_VSCROLL);

	VERIFY(RegisterAsMDI(AFX_WNDMDIFRAME_REG));

	// create with the same wnd-class as MDI-Frame (no erase bkgnd)
	if (!CreateEx(0, AFX_WNDMDIFRAME, NULL, dwCreateStyle, 0, 0, 0, 0,
	  pParentWnd->m_hWnd, (HMENU)nID, NULL))
		return FALSE;       // create invisible

	// attach the initial splitter parts
	TRY
	{
		// create scroll bars by setting the style
		//SetScrollStyle(dwStyle);
	}
	CATCH_ALL(e)
	{
		DestroyWindow(); // will clean up child windows
		// Note: DELETE_EXCEPTION(e) not required
		return FALSE;
	}
	END_CATCH_ALL

	ASSERT(pContext->m_pNewViewClass->IsDerivedFrom(RUNTIME_CLASS(CWnd)));
	m_pCreateContext = pContext;


	return TRUE;	
}


BOOL CDockViewWnd::RegisterAsMDI(LONG fToRegister)
{
	// mask off all classes that are already registered
	AFX_MODULE_STATE* pModuleState = AfxGetModuleState();
	fToRegister &= ~pModuleState->m_fRegisteredClasses;
	if (fToRegister == 0)
		return TRUE;

	LONG fRegisteredClasses = 0;

	// common initialization
	WNDCLASS wndcls;
	memset(&wndcls, 0, sizeof(WNDCLASS));   // start with NULL defaults
	wndcls.lpfnWndProc = AfxGetAfxWndProc();
	wndcls.hInstance = AfxGetInstanceHandle();
	wndcls.hCursor = LoadCursor(AfxGetInstanceHandle(), IDC_ARROW);

	INITCOMMONCONTROLSEX init;
	init.dwSize = sizeof(init);

	// MDI Frame window (also used for splitter window)
	wndcls.style = CS_DBLCLKS;
	wndcls.hbrBackground = NULL;

	wndcls.lpszClassName = AFX_WNDCLASS("MDIFrame");

	HINSTANCE hInst = AfxFindResourceHandle(MAKEINTRESOURCE(AFX_IDI_STD_MDIFRAME), RT_GROUP_ICON);

	if ((wndcls.hIcon = ::LoadIcon(hInst, MAKEINTRESOURCE(AFX_IDI_STD_MDIFRAME))) == NULL)
	{
		// use default icon
		wndcls.hIcon = ::LoadIcon(NULL, IDI_APPLICATION);
	}
	
	if (AfxRegisterClass(&wndcls)) {
		fRegisteredClasses |= AFX_WNDMDIFRAME_REG;
	}

	// save new state of registered controls
	pModuleState->m_fRegisteredClasses |= fRegisteredClasses;

	// must have registered at least as mamy classes as requested
	return (fToRegister & fRegisteredClasses) == fToRegister;

}

BOOL CDockViewWnd::CreateView(CRuntimeClass *pViewClass)
{
#ifdef _DEBUG
	ASSERT_VALID(this);
	ASSERT(pViewClass->IsDerivedFrom(RUNTIME_CLASS(CWnd)));
	ASSERT(AfxIsValidAddress(pViewClass, sizeof(CRuntimeClass), FALSE));
#endif

	BOOL bSendInitialUpdate = FALSE;

	CCreateContext contextT;
	if (m_pCreateContext == NULL)
	{
		// if no context specified, generate one from the currently selected
		//  client if possible
		CView* pOldView = (CView*)GetActiveView();
		if (pOldView != NULL && pOldView->IsKindOf(RUNTIME_CLASS(CView)))
		{
			// set info about last pane
			ASSERT(contextT.m_pCurrentFrame == NULL);
			contextT.m_pLastView = pOldView;
			contextT.m_pCurrentDoc = pOldView->GetDocument();
			if (contextT.m_pCurrentDoc != NULL)
				contextT.m_pNewDocTemplate =
				  contextT.m_pCurrentDoc->GetDocTemplate();
		}
		m_pCreateContext = &contextT;
		bSendInitialUpdate = TRUE;
	}

	// Create a new bar
	CViewBar *pViewBar = new CViewBar();
	if (!pViewBar->Create("Hello", GetParent(), m_uLastID)) {
		return FALSE;
	}

	// Create a new view in the bar
	if (!pViewBar->CreateView(pViewClass, m_pCreateContext, m_uLastID)) {
		return FALSE;
	}

	// Add the bar to our map
	m_aBars.SetAt(m_uLastID, pViewBar);
	
	m_uLastID++;

	return TRUE;
}

CWnd * CDockViewWnd::GetActiveView()
{
	ASSERT_VALID(this);

	// attempt to use active view of frame window
	CWnd* pView = NULL;
	CFrameWnd* pFrameWnd = GetParentFrame();
	ASSERT_VALID(pFrameWnd);
	pView = pFrameWnd->GetActiveView();

	// failing that, use the current focus
	if (pView == NULL)
		pView = GetFocus();

	return pView;
}

POSITION CDockViewWnd::GetFirstBar()
{
	return m_aBars.GetStartPosition();
}

CViewBar * CDockViewWnd::GetNextBar(POSITION &pos)
{
	CViewBar * pViewBar = NULL;
	unsigned short nID = 0;
	m_aBars.GetNextAssoc(pos, nID, (LPVOID &)pViewBar);

	return pViewBar;
}

