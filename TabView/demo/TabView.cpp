/////////////////////////////////////////////////////////////////////////////
// TabView.cpp
//
// Version 1.0, 13. July, 2001
//
// Copyright (C) 2001 by Jean-Pierre Bergamin <james@ractive.ch>
//
// See TabView.h for details
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TabView.h"
#include <afxpriv.h> // Only used for the definition of WM_INITIALUPDATE :-(

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CTabView, CCtrlView)


/////////////////////////////////////////////////////////////////////////////
// CTabView

BEGIN_MESSAGE_MAP(CTabView, CCtrlView)
	//{{AFX_MSG_MAP(CTabView)
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_NOTIFY_REFLECT (TCN_SELCHANGE, OnSelChange)
	ON_NOTIFY_REFLECT (TCN_SELCHANGING, OnSelChanging)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CTabView::~CTabView()
{
	m_Font.DeleteObject();
}

BOOL CTabView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CCtrlView::PreCreateWindow(cs);
}

void CTabView::RemoveImageList()
{
	// Remove the associated image list if there's one
	HIMAGELIST h = (HIMAGELIST)SendMessage(TCM_GETIMAGELIST, NULL, NULL);
	if (CImageList::FromHandlePermanent(h) != NULL) {
		SendMessage(TCM_SETIMAGELIST, NULL, NULL);
	}
}

void CTabView::OnDestroy()
{
	// Clean up...
	m_aPages.RemoveAll();
	m_aPageIDs.RemoveAll();

	RemoveImageList();

	CCtrlView::OnDestroy();
}


/////////////////////////////////////////////////////////////////////////////
// CTabView operations

void CTabView::SetFontHeight(int nHeight)
{
	// Free any memory currently used by the fonts.
	m_Font.DeleteObject();

	// Get the current font
	LOGFONT lFont;
	CFont *pFont = GetFont();
	if (pFont)
		pFont->GetLogFont(&lFont);
	else {
		NONCLIENTMETRICS ncm;
		ncm.cbSize = sizeof(NONCLIENTMETRICS);
		VERIFY(SystemParametersInfo(SPI_GETNONCLIENTMETRICS, sizeof(NONCLIENTMETRICS), &ncm, 0));
		lFont = ncm.lfMessageFont; 
	}

	// Create the "Selected" font
	lFont.lfHeight = -nHeight;
	m_Font.CreateFontIndirect(&lFont);

	SetFont(&m_Font);
}

int CTabView::Insert(LPCTSTR lpszItemText, CRuntimeClass *pNewWnd, CCreateContext *pContext /* = NULL */)
{
	int nPage = GetTabCtrl().GetItemCount();

	return Insert(nPage, lpszItemText, pNewWnd, pContext);
}

int CTabView::Insert(int nPage, LPCTSTR lpszItemText, CRuntimeClass *pNewWnd, CCreateContext *pContext /* = NULL */)
{
	ASSERT(pNewWnd); // Must not be NULL
	ASSERT(pNewWnd->IsDerivedFrom(RUNTIME_CLASS(CWnd))); // Must be a window

	BOOL bSendInitialUpdate = FALSE;

	CCreateContext contextT;
	if (pContext == NULL)
	{
		// if no context specified, generate one from the currently selected
		//  client if possible
		CFrameWnd * pFrameWnd = GetParentFrame();
		CView * pOldView = pFrameWnd->GetActiveView();
		if (pOldView == NULL) {
			// Still no view :-(
			// Use the brute force method...
			pOldView = (CView *)pFrameWnd->GetDescendantWindow(AFX_IDW_PANE_FIRST, TRUE);
			ASSERT(pOldView);	
			// Attention! If you don't have a create context, views are unable
			// to access the document!!
			// If you can live with that, remove this assert but be careful
			// Not to access the document
		}
		if (pOldView != NULL && pOldView->IsKindOf(RUNTIME_CLASS(CView)))
		{
			// set info about last pane
			ASSERT(contextT.m_pCurrentFrame == NULL);
			contextT.m_pLastView = pOldView;
			contextT.m_pCurrentDoc = pOldView->GetDocument();
			if (contextT.m_pCurrentDoc != NULL) {
				contextT.m_pNewDocTemplate = contextT.m_pCurrentDoc->GetDocTemplate();
			}
		}
		pContext = &contextT;
		bSendInitialUpdate = TRUE;
	}

	CTabCtrl &tab = GetTabCtrl();

	CView *pWnd = (CView *)pNewWnd->CreateObject();

	if (!pWnd) {
		return -1;
	}

	ASSERT_KINDOF(CWnd, pWnd); // Make sure we got a window

	// Try to create the new page dynamically
	DWORD dwStyle = WS_CHILD | WS_CLIPCHILDREN | WS_BORDER | WS_VISIBLE;
	if (!pWnd->Create(NULL, NULL, dwStyle, CRect(0, 0, 0, 0), GetParentFrame(), GetNewPageID(nPage), pContext)) {
		return -1;
	}

	int nPages = tab.GetItemCount();

	// Insert the tab
	// nPage will contain the actual page position then
	nPage = tab.InsertItem(nPage, lpszItemText);

	// If the new item position is already taken by another view, we have to assign
	// new values for all the views after the inserted one
	for (int i = nPages - 1; i >= nPage; i--) {
		// Lookup the view first
		CView * pView = GetView(i);
		// Set the new page value in the map
		m_aPages.SetAt(i + 1, pView);
	}

	// Insert the new window pointer into the map
	m_aPages.SetAt(nPage, pWnd);

	// Select the new page if no page is selected
	if (tab.GetCurSel() == -1) {
		tab.SetCurSel(nPage);
	}

	// send initial notification message
	if (bSendInitialUpdate) {
		pWnd->SendMessage(WM_INITIALUPDATE);
	}

	
	// If it the first tab, we activte the view and have to call RecalcLayout
	if (tab.GetItemCount() == 1) {
		GetParentFrame()->SetActiveView(pWnd);
		RecalcLayout(pWnd);
	}

	return nPage;
}

UINT CTabView::GetNewPageID(int nPage)
{
	// Get a new page ID
	m_aPageIDs.SetAt(nPage, ++m_uLastID);

	return m_uLastID;
}

void CTabView::OnSize(UINT nType, int cx, int cy) 
{
	CCtrlView::OnSize(nType, cx, cy);
	
	// At startup we get some WM_SIZE message with the size 0
	// Ignore this
	if (cx <= 0 || cy <= 0) {
		return;
	}
	
	// Recalc the layout of the pages
	RecalcLayout();
}

void CTabView::OnSelChange (NMHDR* pNMHDR, LRESULT* pResult)
{
	CTabCtrl &tab = GetTabCtrl();

	// Get the current selection
	int nSel = tab.GetCurSel ();
	if (nSel == -1)
		return;

	CWnd * pWnd = NULL;
	// Get the associated window
	m_aPages.Lookup(nSel, (LPVOID &)pWnd);
	if (pWnd) {
		// Show the new selected window
		pWnd->ShowWindow(SW_SHOW);
		RecalcLayout(pWnd);

		ASSERT(pWnd->IsKindOf(RUNTIME_CLASS(CView)));
		
		// Set the view as the active view
		CFrameWnd * pFrameWnd = GetParentFrame();
		if (pFrameWnd) {
			pFrameWnd->SetActiveView((CView *)pWnd, TRUE);
		}
	}

	if (pResult) {
		*pResult = 0;
	}
}

void CTabView::OnSelChanging(NMHDR* pNMHDR, LRESULT* pResult)
{
	CTabCtrl &tab = GetTabCtrl();

	// Get the current selection
	int nSel = tab.GetCurSel ();
	if (nSel == -1)
		return;

	CWnd * pWnd = NULL;
	// Get the associated window

	m_aPages.Lookup(nSel, (LPVOID &)pWnd);
	if (pWnd) {
		// Hide the old selected window
		pWnd->ShowWindow(SW_HIDE);
	}

	if (pResult) {
		*pResult = 0;
	}
}

void CTabView::ActivateView(int nItem)
{
	OnSelChanging(NULL, NULL);
	
	// Set the new item as the current selection
	GetTabCtrl().SetCurSel(nItem);

	OnSelChange(NULL, NULL);	
}

void CTabView::RecalcLayout(CWnd *pCurWnd /* = NULL */)
{
	CTabCtrl &tab = GetTabCtrl();
	
	if (pCurWnd == NULL) {
		// Get the selected page
		int nSel = tab.GetCurSel ();
		if (nSel == -1)
			return;

		m_aPages.Lookup(nSel, (LPVOID &)pCurWnd);
	}

	if (pCurWnd) {
		CRect rc;
		GetClientRect(rc);
		// Adjust the size to the tab
		tab.AdjustRect(FALSE, rc);

		CRect tabRect, wRect;
		tab.GetWindowRect(tabRect);
		CFrameWnd * pFrameWnd = GetParentFrame();
		pFrameWnd->GetClientRect(wRect);
		pFrameWnd->ClientToScreen(wRect);
		
		// Move the view down that if fits in the tab
		rc.OffsetRect(1, tabRect.top - wRect.top + 1);

		// And set the window position of the view that it fits (MoveWindow doesn't work...)
		pCurWnd->SetWindowPos(NULL, rc.left, rc.top, rc.Width(), rc.Height(), SWP_SHOWWINDOW);
	}

}

CView * CTabView::GetView(int nView)
{
	// Lookup the view in the map
	CTabCtrl &tab = GetTabCtrl();
	CView * pView = NULL;
	m_aPages.Lookup(nView, (LPVOID &)pView);

	return pView;
}

void CTabView::RemoveView(int nItem)
{
	CTabCtrl &tab = GetTabCtrl();

	// Remove the last view if nItem == -1
	if (nItem == -1) {
		nItem = tab.GetItemCount() - 1;
	}

	CView * pView = GetView(nItem);
	if (!pView) {
		return;
	}

	// Check if the view is currently selected
	if (tab.GetCurSel() == nItem) {
		// If so , activate the previous or the next view
		int nNew = nItem - 1;
		if (nNew == -1) {
			nNew = nItem + 1;
		}

		if (nNew >= 0) {
			ActivateView(nNew);
		}
	}
	

	// Destroy the window. The object is deleted in the CView's PostNcDestroy
	pView->DestroyWindow();

	m_aPages.RemoveKey(nItem);
	m_aPageIDs.RemoveKey(nItem);
	
	tab.DeleteItem(nItem);

	// Now we have to remap the window pointers to the correct page number again
	// This means we have to decrease all pagenumber after the removed one by one
	int nPages = tab.GetItemCount() + 1;
	for(int i = nItem + 1; i < nPages; i++) {
		CView * pView = GetView(i);
		m_aPages.SetAt(i - 1, pView);
	}

}


UINT CTabView::GetPageID(int nPage)
{
	// Lookup the id in the map
	UINT nID = 0;
	m_aPageIDs.Lookup(nPage, nID);

	return nID;
}


void CTabView::RemoveView(CView *pView)
{
	// Search the page where the view resides
	POSITION pos = m_aPages.GetStartPosition();
	while (pos) {
		unsigned short nPage = 0;
		CView * pWnd = NULL;
		m_aPages.GetNextAssoc(pos, nPage, (LPVOID &)pWnd);
		if (pWnd == pView) {
			// We found the page. Remove the view...
			RemoveView(nPage);
			return;
		}

	}

}

