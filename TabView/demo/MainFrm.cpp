// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "TabViewTest.h"
#include "TestTabView.h"
#include "TestHtmlView.h"
#include "NewViewDlg.h"

#include "MyTreeView.h"
#include "MyListView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_REMOVE, OnRemove)
	ON_COMMAND(ID_ADDVIEW, OnAddview)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	if (!m_wndDlgBar.Create(this, IDR_MAINFRAME, 
		CBRS_ALIGN_TOP, AFX_IDW_DIALOGBAR))
	{
		TRACE0("Failed to create dialogbar\n");
		return -1;		// fail to create
	}

	if (!m_wndReBar.Create(this) ||
		!m_wndReBar.AddBar(&m_wndToolBar) ||
		!m_wndReBar.AddBar(&m_wndDlgBar))
	{
		TRACE0("Failed to create rebar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Remove this if you don't want tool tips
	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	if (!CFrameWnd::OnCreateClient(lpcs, pContext)) {
		return FALSE;
	}

	// The TabView is already created, but not set as the active view yet! (but why?)
	// This requires this hack to get the pointer to the view
	CWnd* pWnd = GetDescendantWindow(AFX_IDW_PANE_FIRST, TRUE);
	if (pWnd != NULL && pWnd->IsKindOf(pContext->m_pNewViewClass))
	{
		CTestTabView* pView = (CTestTabView*)pWnd;
		
		m_pTabView = pView;

		// Here you can add your dialogs and views and whatever you like....
		if (pView->Insert(0, "Browser", RUNTIME_CLASS(CTestHtmlView), pContext) == -1) {
			return FALSE;
		}
		if (pView->Insert(1, "Bookmarks", RUNTIME_CLASS(CMyTreeView), pContext) == -1) {
			return FALSE;
		}
		if (pView->Insert(2, "Sample List", RUNTIME_CLASS(CMyListView), pContext) == -1) {
			return FALSE;
		}
	}

	return TRUE;
}

void CMainFrame::OnRemove() 
{
	// Remove the last view (-1)
	// If you want to remove a specific view, pass the correct value
	//m_pTabView->RemoveView(-1);
	m_pTabView->RemoveView(GetActiveView());
}

void CMainFrame::OnAddview() 
{
	CNewViewDlg dlg;
	if (dlg.DoModal() == IDCANCEL) {
		return;
	}
	// Insert a new view on the last position (-1)
	m_pTabView->Insert(dlg.m_nPosition, dlg.m_sTabLabel, dlg.m_pRuntimeClass);	
}
